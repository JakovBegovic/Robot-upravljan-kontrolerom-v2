#pragma once
#include <Arduino.h>

namespace HardwareReader
{
    /*
    * HardwareReader public functions and variables
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
};

namespace
{
    /*
    * HardwareReader private functions and variables
    */

    // forward, backward, right, left, music
    const uint8_t btnPINs[ 5 ] = { 12, 13, 14, 15, 23 };
    const uint8_t potentioPIN = 35;

    void setupBTNs()
    {
        for ( int i = 0; i < sizeof( btnPINs ) / sizeof( uint8_t ); i++ )
        {
            pinMode( btnPINs[ i ], INPUT_PULLUP );
        }
    }

    void setupADC()
    {
        analogReadResolution( 12 );
    }
}