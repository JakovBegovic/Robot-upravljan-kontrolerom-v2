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

    if( commsController.shouldSendMsg() )
    {
        result = commsController.sendConstructedMessage();

        if( DEBUG )
        {
            Serial.print( "Sent " );
            Serial.print( commsController.constructedMsg.speed );
            Serial.print( "   time: " );
            Serial.println( ( double )millis() / 1000 );
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