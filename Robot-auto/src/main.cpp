#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

const uint8_t ledPINs[ 5 ] = { 12, 13, 14, 15, 23 };

const uint8_t macAdressRobotCar[] = { 0x7C, 0x87, 0xCE, 0xF8, 0xCA, 0xE8 };
const uint8_t macAdressController[] = { 0x94, 0xE6, 0x86, 0xA8, 0x61, 0x24 };

uint8_t recievedCommand = 0;

struct
{
    uint8_t command;
} recievedMessage;

esp_now_peer_info_t espNowPeerInfo;

void onDataRecieved( const uint8_t * macAddress, const uint8_t *recievedData, int length );

void controlLEDs( uint8_t ledNumber );


void setup()
{
    Serial.begin( 115200 );

    for ( int i = 0; i < 5; i++ )
    {
        pinMode( ledPINs[ i ], OUTPUT );
        digitalWrite( ledPINs[ i ], LOW );
    }


    WiFi.mode( WIFI_STA );

    if ( esp_now_init() != ESP_OK )
    {
        Serial.println( "Error initializing ESP-NOW" );
        return;
    }

    memcpy( espNowPeerInfo.peer_addr, macAdressController, 6 );
    espNowPeerInfo.channel = 0;
    espNowPeerInfo.encrypt = false;

    if ( esp_now_add_peer(&espNowPeerInfo ) != ESP_OK )
    {
        Serial.println( "Failed to add peer" );
        return;
    }

    esp_now_register_recv_cb( onDataRecieved );
}

void loop()
{
}

void onDataRecieved( const uint8_t *macAddress, const uint8_t *recievedData, int length )
{
    memcpy( &recievedMessage, recievedData, sizeof( recievedMessage ) );

    recievedCommand = recievedMessage.command;

    controlLEDs( recievedCommand );
}

void controlLEDs( uint8_t ledNumber )
{
    for ( int i = 0; i < 5; i++ )
    {
        digitalWrite( ledPINs[ i ], LOW );
    }

    digitalWrite( ledPINs[ ledNumber ], HIGH );
}
