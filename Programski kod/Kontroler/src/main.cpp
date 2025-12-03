#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

const uint8_t btnPINs[ 5 ] = { 12, 13, 14, 15, 23 };

enum
{
    STOP = 0,
    LEFT,
    RIGHT,
    FRWRD,
    BCKWRD
};

uint8_t readInputs();


const uint8_t macAdressRobotCar[] = { 0x7C, 0x87, 0xCE, 0xF8, 0xCA, 0xE8 };
const uint8_t macAdressController[] = { 0x94, 0xE6, 0x86, 0xA8, 0x61, 0x24 };

unsigned long lastTimeMsgSent = 0;
unsigned long timeBetweenMsgs = 50; // in miliseconds

struct
{
    uint8_t command;
} outgoingMessage;

esp_now_peer_info_t espNowPeerInfo;
esp_now_send_status_t lastMsgStatus = ESP_NOW_SEND_FAIL;

void onDataSent( const uint8_t *macAddress, esp_now_send_status_t status );

esp_err_t sendMessage( uint8_t message );


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
    static uint8_t messageToSend = STOP;
    static uint8_t lastMessageSent = STOP;

    messageToSend = readInputs();

    esp_err_t result;

    if( messageToSend != lastMessageSent ||
        lastMsgStatus == ESP_NOW_SEND_FAIL ||
        ( messageToSend != STOP &&
          millis() - lastTimeMsgSent > 500 )
      )
    {
        result = sendMessage( messageToSend );

        if( result == ESP_OK )
        {
            lastMessageSent = messageToSend;
        }
    }
}

uint8_t readInputs()
{
    uint8_t messageToSend;

    if( !digitalRead( btnPINs[ 3 ] ) )
    {
        messageToSend = BCKWRD;
    }
    else if( !digitalRead( btnPINs[ 2 ] ) )
    {
        messageToSend = FRWRD;
    }
    else if( !digitalRead( btnPINs[ 1 ] ) )
    {
        messageToSend = RIGHT;
    }
    else if( !digitalRead( btnPINs[ 0 ] ) )
    {
        messageToSend = LEFT;
    }
    else
    {
        messageToSend = STOP;
    }

    return messageToSend;
}

void onDataSent( const uint8_t *macAddress, esp_now_send_status_t status )
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

esp_err_t sendMessage( uint8_t message )
{
    esp_err_t result;

    if( millis() - lastTimeMsgSent > timeBetweenMsgs )
    {
        lastTimeMsgSent = millis();

        outgoingMessage.command = message;
        result = esp_now_send( macAdressRobotCar, ( uint8_t * ) &outgoingMessage, sizeof( outgoingMessage ) );
    }
    else
    {
        result = ESP_FAIL;
    }

    return result;
}
