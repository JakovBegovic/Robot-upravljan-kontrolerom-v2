#pragma once
#include <Arduino.h>

#include "HrdwrController.h"

namespace Tasker
{
    /*
    *   Tasker public functions
    */

    /**
    * @brief   Setup all the tasks that run in this program
    */
    void setupTasks( TaskHandle_t mainTaskHandle );

    /**
    * @brief   Getter for musicTaskHandle variable
    */
    TaskHandle_t getMusicTaskHandle();
}