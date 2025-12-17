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
    commsController.constructMsg( hardwareReader );

    esp_err_t result;

    if( (
            (
                commsController.constructedMsg != commsController.lastMessageSent ||
                commsController.failedMsgsInARow > 0 &&
                commsController.failedMsgsInARow < 20
            )
            &&
            millis() - commsController.lastTimeMsgSent > 50
        )
        ||
        (
            (
                commsController.constructedMsg.moveDirection != 0 ||
                commsController.constructedMsg.rotation != 0
            )
            &&
            millis() - commsController.lastTimeMsgSent > 500
        )
      )
    {
        result = commsController.sendMessage( &commsController.constructedMsg );

        if( DEBUG )
        {
            Serial.print( "Sent " );
            Serial.print( commsController.constructedMsg.speed );
            Serial.print( "   time: " );
            Serial.println( ( double )millis() / 1000 );
        }

        if( result == ESP_OK )
        {
            commsController.lastMessageSent.moveDirection = commsController.constructedMsg.moveDirection;
            commsController.lastMessageSent.rotation = commsController.constructedMsg.rotation;
            commsController.lastMessageSent.speed = commsController.constructedMsg.speed;
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