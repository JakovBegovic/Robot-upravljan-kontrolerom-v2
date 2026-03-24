#pragma once
#include <Arduino.h>
#include <cmath>

#include "HrdwrController.h"

namespace HrdwrReader
{
    /*
    *   HrdwrReader public functions
    */

    /**
     * @brief   Setup communication with hardware pheripherals
     */
    void setup();

    /**
    * @brief    Get user command on move direction
     *
     * @return
     *          1 : forward
     *          0 : stop frontal movement
     *          -1 : backward
    */
    int8_t getMoveDir();

    /**
     * @brief   Get user command on rotation
     *
     * @return
     *          1 : right
     *          0 : stop rotation
     *          -1 : left
     */
    int8_t getRotation();

    /**
    * @brief    Get user command on speed
     *
     * @return
     *          0 to 4095
    */
    uint16_t getSpeed();

    /**
    * @brief    Get user input on music button
     *
     * @return
     *          1 : pressed
     *          0 : not pressed
    */
    bool readMusicBtn();

    float readBttryVoltage();
};