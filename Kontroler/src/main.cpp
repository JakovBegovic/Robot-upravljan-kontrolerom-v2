#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

const uint8_t btnPINs[ 5 ] = { 12, 13, 14, 15, 23 };

const uint8_t macAdressRobotCar[] = { 0x7C, 0x87, 0xCE, 0xF8, 0xCA, 0xE8 };
const uint8_t macAdressController[] = { 0x94, 0xE6, 0x86, 0xA8, 0x61, 0x24 };

struct
{
    uint8_t command;
} outgoingMessage;

esp_now_peer_info_t espNowPeerInfo;

void onDataSent( const uint8_t *macAddr, esp_now_send_status_t status );

void sendMessage( uint8_t message );


void setup()
{
    Serial.begin( 115200 );

    for ( int i = 0; i < 5; i++ )
    {
        pinMode( btnPINs[ i ], INPUT_PULLUP );
    }


    WiFi.mode( WIFI_STA );

    if ( esp_now_init() != ESP_OK )
    {
        Serial.println( "Error initializing ESP-NOW" );
        return;
    }

    memcpy( espNowPeerInfo.peer_addr, macAdressRobotCar, 6 );
    espNowPeerInfo.channel = 0;
    espNowPeerInfo.encrypt = false;

    if ( esp_now_add_peer( &espNowPeerInfo ) != ESP_OK )
    {
        Serial.println( "Failed to add peer" );
        return;
    }

    esp_now_register_send_cb( onDataSent );
}

void loop()
{
    if( !digitalRead( btnPINs[ 3 ] ) )
    {
        sendMessage( 4 );
    }
    else if( !digitalRead( btnPINs[ 2 ] ) )
    {
        sendMessage( 3 );
    }
    else if( !digitalRead( btnPINs[ 1 ] ) )
    {
        sendMessage( 2 );
    }
    else if( !digitalRead( btnPINs[ 0 ] ) )
    {
        sendMessage( 1 );
    }
    else
    {
        sendMessage( 0 );
    }

    //Serial.println(outgoingMessage.command);
}

void onDataSent( const uint8_t *macAddr, esp_now_send_status_t status )
{
    Serial.println( status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail" );
}

void sendMessage( uint8_t message )
{
    outgoingMessage.command = message;

    static unsigned long lastTimeSent = 0;

    if( millis() - lastTimeSent > 50 )
    {
        lastTimeSent = millis();

        esp_err_t result = esp_now_send( macAdressRobotCar, ( uint8_t * ) &outgoingMessage, sizeof( outgoingMessage ) );
    }
}
