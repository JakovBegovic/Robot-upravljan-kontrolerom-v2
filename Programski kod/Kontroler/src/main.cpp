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

    CommsController::setup();

    HrdwrReader::setup();

    HrdwrController::setup();

    if( DEBUG )
    {
        Serial.println( tskIDLE_PRIORITY );
        Serial.println( configMAX_PRIORITIES );
        Serial.println( uxTaskPriorityGet( NULL ) );
        Serial.println( xPortGetCoreID() );
    }
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

    vTaskDelay( 50 / portTICK_PERIOD_MS );
}