#include "HardwareReader.h"

namespace
{
    /*
    *   HardwareReader private variables
    */

    // forward, backward, right, left, music
    const uint8_t btnPINs[ 5 ] = { 12, 13, 14, 15, 23 };
    const uint8_t potentioPIN = 35;

    unsigned long lastInterrupt = 0;


    /*
    *   HardwareReader private functions
    */

    void IRAM_ATTR musicButtonISR()
    {
        if( millis() - lastInterrupt > 200 )
        {
            lastInterrupt = millis();

            HrdwrController::playNextSong();
        }

    }

    void setupBTNs()
    {
        for ( int i = 0; i < sizeof( btnPINs ) / sizeof( uint8_t ); i++ )
        {
            pinMode( btnPINs[ i ], INPUT_PULLUP );
        }

        attachInterrupt( btnPINs[ 4 ], musicButtonISR, FALLING );
    }

    void setupADC()
    {
        analogReadResolution( 12 );
    }
}


/*
*   HardwareReader public function definitions
*/

void HardwareReader::setup()
{
    setupBTNs();
    setupADC();
}

int8_t HardwareReader::getMoveDir()
{
    return !digitalRead( btnPINs[ 0 ] ) - !digitalRead( btnPINs[ 1 ] );
}

int8_t HardwareReader::getRotation()
{
    return !digitalRead( btnPINs[ 2 ] ) - !digitalRead( btnPINs[ 3 ] );
}

uint16_t HardwareReader::getSpeed()
{
    return analogRead( potentioPIN );
}
