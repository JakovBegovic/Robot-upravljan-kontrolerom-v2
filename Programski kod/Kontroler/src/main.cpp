#include <Arduino.h>

#include "HrdwrReader.h"
#include "HrdwrController.h"
#include "CommsController.h"
#include "Tasker.h"

#define DEBUG 0


void setup()
{
    if( DEBUG )
    {
        Serial.begin( 115200 );
    }

    CommsController::setup();

    HrdwrReader::setup();

    HrdwrController::setup();

    Tasker::setupTasks( xTaskGetCurrentTaskHandle() );

    if( DEBUG )
    {
        Serial.println( uxTaskPriorityGet( NULL ) );
        Serial.println( uxTaskPriorityGet( xTaskGetCurrentTaskHandle() ) );
        Serial.println( xPortGetCoreID() );
    }
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