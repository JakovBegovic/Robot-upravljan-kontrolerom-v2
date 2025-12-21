#pragma once
#include <Arduino.h>

#include "CommsController.h"


namespace HrdwrController
{
    /*
    *   HrdwrController public functions
    */

    /**
    * @brief   Setup control over hardware pheripherals
    */
    void setup();

    /**
    * @brief   Change which LEDs are active
    */
    void controlLEDs( msgStruct msg );
}