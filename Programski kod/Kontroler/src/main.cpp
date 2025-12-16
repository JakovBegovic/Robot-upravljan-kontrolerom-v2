#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "HardwareReader.h"

#define DEBUG 1

HardwareReader hardwareReader;

struct msgStruct
{
    int8_t moveDirection = 0; // 0 stop, 1 forward, -1 backward
    int8_t rotation = 0; // 0 no rotation, 1 right, -1 left
    uint16_t speed = 2048; // 0 to 4095
};

bool operator!=( const msgStruct& a, const msgStruct& b );

void constructMsg( msgStruct* msgToConstruct );


const uint8_t macAdressRobotCar[] = { 0x7C, 0x87, 0xCE, 0xF8, 0xCA, 0xE8 };
const uint8_t macAdressController[] = { 0x94, 0xE6, 0x86, 0xA8, 0x61, 0x24 };

unsigned long lastTimeMsgSent = 0;
uint8_t failedMsgsInARow = 0;

esp_now_peer_info_t espNowPeerInfo;

void onDataSent( const uint8_t* macAddress, esp_now_send_status_t status );

esp_err_t sendMessage( const msgStruct* msgToConstruct );


void setup()
{
    if( DEBUG )
    {
        Serial.begin( 115200 );
    }

    hardwareReader.setup();

    WiFi.mode( WIFI_STA );

    if ( esp_now_init() != ESP_OK )
    {
        if( DEBUG )
        {
            Serial.println( "Error initializing ESP-NOW" );
        }

        return;
    }

    memcpy( espNowPeerInfo.peer_addr, macAdressRobotCar, 6 );
    espNowPeerInfo.channel = 0;
    espNowPeerInfo.encrypt = false;

    if ( esp_now_add_peer( &espNowPeerInfo ) != ESP_OK )
    {
        if( DEBUG )
        {
            Serial.println( "Failed to add peer" );
        }

        return;
    }

    esp_now_register_send_cb( onDataSent );
}

void loop()
{
    static msgStruct messageToSend;
    static msgStruct lastMessageSent;

    constructMsg( &messageToSend );

    esp_err_t result;

    if( (
            (
                messageToSend != lastMessageSent ||
                failedMsgsInARow > 0 &&
                failedMsgsInARow < 20
            )
            &&
            millis() - lastTimeMsgSent > 50
        )
        ||
        (
            (
                messageToSend.moveDirection != 0 ||
                messageToSend.rotation != 0
            )
            &&
            millis() - lastTimeMsgSent > 500
        )
      )
    {
        result = sendMessage( &messageToSend );

        if( result == ESP_OK )
        {
            lastMessageSent.moveDirection = messageToSend.moveDirection;
            lastMessageSent.rotation = messageToSend.rotation;
            lastMessageSent.speed = messageToSend.speed;
        }
    }
}

void constructMsg( msgStruct* msgToConstruct )
{
    // digitalRead returns 0 for pressed button and 1 for unpressed button

    msgToConstruct->moveDirection = hardwareReader.getMoveDir();
    msgToConstruct->rotation = hardwareReader.getRotation();
    msgToConstruct->speed = hardwareReader.getSpeed();
}

esp_err_t sendMessage( const msgStruct* outgoingMessage )
{
    esp_err_t result;

    result = esp_now_send( macAdressRobotCar, ( uint8_t* ) outgoingMessage, sizeof( *outgoingMessage ) );

    lastTimeMsgSent = millis();

    if( DEBUG )
    {
        Serial.print( "Sent " );
        Serial.print( outgoingMessage->speed );
        Serial.print( "  " );
        Serial.println( ( double )millis() / 1000 );
    }

    return result;
}

void onDataSent( const uint8_t* macAddress, esp_now_send_status_t status )
{
    if( status == ESP_NOW_SEND_FAIL )
    {
        failedMsgsInARow++;
    }
    else
    {
        failedMsgsInARow = 0;
    }
}

bool operator!=( const msgStruct& a, const msgStruct& b )
{
    return a.moveDirection != b.moveDirection ||
           a.rotation != b.rotation ||
           !(
               a.speed - 200 <= b.speed &&
               a.speed + 200 >= b.speed
           );
}
