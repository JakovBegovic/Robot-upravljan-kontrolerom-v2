#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "CommsController.h"
#include "HrdwrController.h"

#define DEBUG 1

void setup()
{
    if( DEBUG )
    {
        Serial.begin( 115200 );
    }

    if( DEBUG )
    {
        Serial.println( CommsController::setup() );
    }

    HrdwrController::setup();
}

void loop()
{
    if( DEBUG )
    {
        Serial.print( "Move: " );
        Serial.print( CommsController::getRecievedMsg().moveDirection );
        Serial.print( "  rotation: " );
        Serial.print( CommsController::getRecievedMsg().rotation );
        Serial.print( "  timeReciev: " );
        Serial.println( CommsController::getLastTimeRcvdMsg() );

        delay( 50 );
    }

    if(
        (
            CommsController::getRecievedMsg().moveDirection != 0 ||
            CommsController::getRecievedMsg().rotation != 0
        )
        &&
        millis() - CommsController::getLastTimeRcvdMsg() > 600
    )
    {
        CommsController::setRecievedMsg( 0, 0, 2047 );

        HrdwrController::controlLEDs( CommsController::getRecievedMsg().moveDirection, CommsController::getRecievedMsg().rotation );
    }
}
