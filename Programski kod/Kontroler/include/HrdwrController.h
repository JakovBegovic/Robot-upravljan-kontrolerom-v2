#pragma once
#include <Arduino.h>
#include <pitches.h>
#include "HrdwrReader.h"

namespace HrdwrController
{
    /*
    *   HrdwrController public functions
    */

    /**
     * @brief   Change song currently playing on buzzer
     */
    void setup();

    /**
    * @brief   Play charge me request on buzzer
    */
    void requestCharging();
}