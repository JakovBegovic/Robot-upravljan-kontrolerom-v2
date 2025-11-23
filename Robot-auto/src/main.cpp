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
} incomingMessage;

esp_now_peer_info_t espNowPeerInfo;

void onDataRecv( const uint8_t * macAddr, const uint8_t *incomingData, int len );


void setup()
{
    Serial.begin( 115200 );

    for ( int i = 0; i < 5; i++ )
    {
        pinMode( ledPINs[ i ], OUTPUT );
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

    esp_now_register_recv_cb( onDataRecv );
}

void loop()
{
    for ( int i = 0; i < 5; i++ )
    {
        digitalWrite( ledPINs[ i ], LOW );
    }

    delay( 200 );
    digitalWrite( ledPINs[ recievedCommand ], HIGH );
    delay( 200 );
}

void onDataRecv( const uint8_t *macAddr, const uint8_t *incomingData, int len )
{
    memcpy( &incomingMessage, incomingData, sizeof( incomingMessage ) );

    recievedCommand = incomingMessage.command;
}
