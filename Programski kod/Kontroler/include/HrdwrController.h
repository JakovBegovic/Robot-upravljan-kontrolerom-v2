#pragma once
#include <Arduino.h>

#include <pitches.h>

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
     * @brief   Play songs on buzzer
     */
    void playSong( void *pvParameter );

    /**
     * @brief   Play next song on buzzer
     */
    void playNextSong( );

    /**
     * @brief   Stop playing songs on buzzer
     */
    void stopPlaying();

    /**
    * @brief   Play charge me request on buzzer
    */
    void requestCharging();
}