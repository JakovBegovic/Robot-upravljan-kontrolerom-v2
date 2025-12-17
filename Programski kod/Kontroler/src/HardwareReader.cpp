#include "HardwareReader.h"

namespace
{
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

namespace HardwareReader
{
    void setup()
    {
        setupBTNs();
        setupADC();
    }

    int8_t getMoveDir()
    {
        return !digitalRead( btnPINs[ 0 ] ) - !digitalRead( btnPINs[ 1 ] );
    }

    int8_t getRotation()
    {
        return !digitalRead( btnPINs[ 2 ] ) - !digitalRead( btnPINs[ 3 ] );
    }

    uint16_t getSpeed()
    {
        return analogRead( potentioPIN );
    }
}