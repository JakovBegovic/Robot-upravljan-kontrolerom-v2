#include "HardwareReader.h"

void HardwareReader::setupADC()
{
    analogReadResolution( 12 );
}

void HardwareReader::setupBTNs()
{
    for ( int i = 0; i < sizeof( btnPINs ) / sizeof( uint8_t ); i++ )
    {
        pinMode( btnPINs[ i ], INPUT_PULLUP );
    }
}

void HardwareReader::setup()
{
    HardwareReader::setupBTNs();
    HardwareReader::setupADC();
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