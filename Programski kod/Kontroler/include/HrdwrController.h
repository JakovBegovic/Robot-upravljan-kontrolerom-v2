#pragma once
#include <Arduino.h>
#include <pitches.h>

#include "HrdwrReader.h"
#include "Tasker.h"

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

    /**
    * @brief   Task logic for playing songs on buzzer
    */
    void playSongTask( void *pvParameter );

    /**
    * @brief   Task logic for controlling the song player
    */
    void musicCtrlTask( void *pvParameter );
}