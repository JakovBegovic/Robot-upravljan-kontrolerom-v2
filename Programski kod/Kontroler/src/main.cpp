#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "HardwareReader.h"
#include "CommsController.h"

#define DEBUG 1


void dataRecievedInfo( const uint8_t* macAddress, esp_now_send_status_t status );


void setup()
{
    if( DEBUG )
    {
        Serial.begin( 115200 );
    }

    HardwareReader::setup();

    CommsController::setup();

    esp_now_register_send_cb( dataRecievedInfo );
}

void loop()
{
    CommsController::constructMsg();

    if( CommsController::shouldSendMsg() )
    {
        esp_err_t result = CommsController::sendConstructedMsg();

        if( DEBUG )
        {
            Serial.print( "Sent " );
            Serial.print( CommsController::getConstructedMsg().speed );
            Serial.print( "   time: " );
            Serial.println( ( double )millis() / 1000 );
        }
    }
}

void dataRecievedInfo( const uint8_t* macAddress, esp_now_send_status_t status )
{
    CommsController::setFailedMsgsInARow( status );
}