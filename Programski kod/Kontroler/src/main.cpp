#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "HrdwrReader.h"
#include "HrdwrController.h"
#include "CommsController.h"

#define DEBUG 0

void setup()
{
    if( DEBUG )
    {
        Serial.begin( 115200 );
    }

    vTaskPrioritySet( NULL, 2 );

    if( DEBUG )
    {
        Serial.println( uxTaskPriorityGet( NULL ) );
        Serial.println( xPortGetCoreID() );
    }


    CommsController::setup();

    HrdwrReader::setup();

    HrdwrController::setup();
}

void loop()
{
    CommsController::constructMsg();

    if( CommsController::shouldSendMsg() )
    {
        esp_err_t result = CommsController::sendConstructedMsg();
    }

    vTaskDelay( CommsController::getMinTimeBetweenMsgs() / portTICK_PERIOD_MS );
}