#include <Arduino.h>
#include <driver/mcpwm.h>

#include "CommsController.h"
#include "HrdwrController.h"

#define DEBUG 0

void setup()
{
    if( DEBUG )
    {
        Serial.begin( 115200 );
    }

    CommsController::setup();

    HrdwrController::setup();
}

void loop()
{
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

        HrdwrController::controlLEDs( CommsController::getRecievedMsg() );
    }
}
