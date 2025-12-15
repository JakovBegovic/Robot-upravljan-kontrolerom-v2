#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#define DEBUG 0

const uint8_t ledPINs[ 6 ] = { 12, 13, 14, 15, 23, 19 };

const uint8_t macAdressRobotCar[] = { 0x7C, 0x87, 0xCE, 0xF8, 0xCA, 0xE8 };
const uint8_t macAdressController[] = { 0x94, 0xE6, 0x86, 0xA8, 0x61, 0x24 };

unsigned long lastTimeRcvdMsg = 0;

struct
{
    int8_t moveDirection = 0; // 0 stop, 1 forward, -1 backward
    int8_t rotation = 0; // 0 no rotation, 1 right, -1 left
    uint16_t speed = 2048; // 0 to 4095
} recievedMessage;

esp_now_peer_info_t espNowPeerInfo;

void onDataRecieved( const uint8_t * macAddress, const uint8_t *recievedData, int length );

void controlLEDs( int8_t moveDirection, int8_t rotation );


void setup()
{
    if( DEBUG )
    {
        Serial.begin( 115200 );
    }

    for ( int i = 0; i < 6; i++ )
    {
        pinMode( ledPINs[ i ], OUTPUT );
    }

    controlLEDs( recievedMessage.moveDirection, recievedMessage.rotation );


    WiFi.mode( WIFI_STA );

    if ( esp_now_init() != ESP_OK )
    {
        if( DEBUG )
        {
            Serial.println( "Error initializing ESP-NOW" );
        }

        return;
    }

    memcpy( espNowPeerInfo.peer_addr, macAdressController, 6 );
    espNowPeerInfo.channel = 0;
    espNowPeerInfo.encrypt = false;

    if ( esp_now_add_peer(&espNowPeerInfo ) != ESP_OK )
    {
        if( DEBUG )
        {
            Serial.println( "Failed to add peer" );
        }

        return;
    }

    esp_now_register_recv_cb( onDataRecieved );
}

void loop()
{
    if(
        (
            recievedMessage.moveDirection != 0 ||
            recievedMessage.rotation != 0
        )
        &&
        millis() - lastTimeRcvdMsg > 600
    )
    {
        recievedMessage.moveDirection = 0;
        recievedMessage.rotation = 0;

        controlLEDs( recievedMessage.moveDirection, recievedMessage.rotation );
    }
}

void onDataRecieved( const uint8_t *macAddress, const uint8_t *recievedData, int length )
{
    memcpy( &recievedMessage, recievedData, sizeof( recievedMessage ) );

    lastTimeRcvdMsg = millis();

    controlLEDs( recievedMessage.moveDirection, recievedMessage.rotation );
}

void controlLEDs( int8_t moveDirection, int8_t rotation )
{
    for ( int i = 0; i < 6; i++ )
    {
        digitalWrite( ledPINs[ i ], LOW );
    }

    digitalWrite( ledPINs[ 1 + moveDirection ], HIGH );

    digitalWrite( ledPINs[ 4 + rotation ], HIGH );
}
