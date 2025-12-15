#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#define DEBUG 0

// forward, backward, right, left, music
const uint8_t btnPINs[ 5 ] = { 12, 13, 14, 15, 23 };


struct msgStruct
{
    int8_t moveDirection = 0; // 0 stop, 1 forward, -1 backward
    int8_t rotation = 0; // 0 no rotation, 1 right, -1 left
    int16_t speed = 2048; // 0 to 4096
};

bool operator!=( const msgStruct& a, const msgStruct& b );

void constructMsg( msgStruct* msgToConstruct );


const uint8_t macAdressRobotCar[] = { 0x7C, 0x87, 0xCE, 0xF8, 0xCA, 0xE8 };
const uint8_t macAdressController[] = { 0x94, 0xE6, 0x86, 0xA8, 0x61, 0x24 };

unsigned long lastTimeMsgSent = 0;
unsigned long timeBetweenMsgs = 50; // in miliseconds

esp_now_peer_info_t espNowPeerInfo;
esp_now_send_status_t lastMsgStatus = ESP_NOW_SEND_SUCCESS;

void onDataSent( const uint8_t* macAddress, esp_now_send_status_t status );

esp_err_t sendMessage( const msgStruct* msgToConstruct );


void setup()
{
    if( DEBUG )
    {
        Serial.begin( 115200 );
    }

    for ( int i = 0; i < 5; i++ )
    {
        pinMode( btnPINs[ i ], INPUT_PULLUP );
    }


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
                lastMsgStatus == ESP_NOW_SEND_FAIL
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

    msgToConstruct->moveDirection = !digitalRead( btnPINs[ 0 ] ) - !digitalRead( btnPINs[ 1 ] );
    msgToConstruct->rotation = !digitalRead( btnPINs[ 2 ] ) - !digitalRead( btnPINs[ 3 ] );
    msgToConstruct->speed = 2048;
}

esp_err_t sendMessage( const msgStruct* outgoingMessage )
{
    esp_err_t result;

    result = esp_now_send( macAdressRobotCar, ( uint8_t* ) outgoingMessage, sizeof( *outgoingMessage ) );

    lastTimeMsgSent = millis();

    if( DEBUG )
    {
        Serial.print( "Sent " );
        Serial.println( ( double )millis() / 1000 );
    }

    return result;
}

void onDataSent( const uint8_t* macAddress, esp_now_send_status_t status )
{
    lastMsgStatus = status;

    static uint8_t failedInARow = 0;

    if( lastMsgStatus == ESP_NOW_SEND_FAIL )
    {
        ++failedInARow;

        if( failedInARow == 10 )
        {
            timeBetweenMsgs = 500;
        }
    }
    else
    {
        failedInARow = 0;
        timeBetweenMsgs = 50;
    }
}

bool operator!=( const msgStruct& a, const msgStruct& b )
{
    return a.moveDirection != b.moveDirection ||
           a.rotation != b.rotation ||
           a.speed != b.speed;
}
