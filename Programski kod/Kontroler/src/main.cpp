#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "HardwareReader.h"
#include "CommsController.h"
#include "MsgStruct.h"

#define DEBUG 1

HardwareReader hardwareReader;

CommsController commsController;


void onDataSent( const uint8_t* macAddress, esp_now_send_status_t status );


void setup()
{
    if( DEBUG )
    {
        Serial.begin( 115200 );
    }

    hardwareReader.setup();

    commsController.setup();

    esp_now_register_send_cb( onDataSent );
}

void loop()
{
    static msgStruct messageToSend;
    static msgStruct lastMessageSent;

    commsController.constructMsg( &messageToSend, hardwareReader );

    esp_err_t result;

    if( (
            (
                messageToSend != lastMessageSent ||
                commsController.failedMsgsInARow > 0 &&
                commsController.failedMsgsInARow < 20
            )
            &&
            millis() - commsController.lastTimeMsgSent > 50
        )
        ||
        (
            (
                messageToSend.moveDirection != 0 ||
                messageToSend.rotation != 0
            )
            &&
            millis() - commsController.lastTimeMsgSent > 500
        )
      )
    {
        result = commsController.sendMessage( &messageToSend );

        if( DEBUG )
        {
            Serial.print( "Sent " );
            Serial.print( messageToSend.speed );
            Serial.print( "   time: " );
            Serial.println( ( double )millis() / 1000 );
        }

        if( result == ESP_OK )
        {
            lastMessageSent.moveDirection = messageToSend.moveDirection;
            lastMessageSent.rotation = messageToSend.rotation;
            lastMessageSent.speed = messageToSend.speed;
        }
    }
}


void onDataSent( const uint8_t* macAddress, esp_now_send_status_t status )
{
    if( status == ESP_NOW_SEND_FAIL )
    {
        commsController.failedMsgsInARow++;
    }
    else
    {
        commsController.failedMsgsInARow = 0;
    }
}