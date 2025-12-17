#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "HardwareReader.h"
#include "CommsController.h"

#define DEBUG 1

void setup()
{
    if( DEBUG )
    {
        Serial.begin( 115200 );
    }

    HardwareReader::setup();

    CommsController::setup();

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