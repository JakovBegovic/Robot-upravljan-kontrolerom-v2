#include "HrdwrReader.h"

namespace
{
    /*
    *   HrdwrReader private variables
    */

    // forward, backward, right, left, music
    const uint8_t btnPINs[ 5 ] = { 12, 13, 14, 15, 23 };
    const uint8_t potentioPIN = 35;

    const uint8_t bttryReadPIN = 39;
    const uint8_t adcResolution = 12;
    const adc_attenuation_t adcAttenBttryPin = ADC_11db;

    const int R1 = 1e3f;
    const int R2 = 1e3f;
    const float voltageDvsnInverse = ( float ) ( R1 + R2 ) / R2;
    const float lsbToVoltageRatio = 0.000806f; // 3.3 / (2^12 - 1)

    unsigned long lastInterrupt = 0;



    /*
    *   HrdwrReader private functions
    */

    void setupBTNs()
    {
        for ( int i = 0; i < sizeof( btnPINs ) / sizeof( uint8_t ); i++ )
        {
            pinMode( btnPINs[ i ], INPUT_PULLUP );
        }
    }

    void setupADC()
    {
        analogReadResolution( adcResolution );
        analogSetPinAttenuation( bttryReadPIN, adcAttenBttryPin );
    }
}


/*
*   HrdwrReader public function definitions
*/

void HrdwrReader::setup()
{
    setupBTNs();
    setupADC();
}

int8_t HrdwrReader::getMoveDir()
{
    return !digitalRead( btnPINs[ 0 ] ) - !digitalRead( btnPINs[ 1 ] );
}

int8_t HrdwrReader::getRotation()
{
    return !digitalRead( btnPINs[ 2 ] ) - !digitalRead( btnPINs[ 3 ] );
}

uint16_t HrdwrReader::getSpeed()
{
    return analogRead( potentioPIN );
}

bool HrdwrReader::readMusicBtn()
{
    return !digitalRead( btnPINs[ 4 ] );
}

float HrdwrReader::readBttryVoltage()
{
    return ( float )analogRead( bttryReadPIN ) * voltageDvsnInverse * lsbToVoltageRatio;
}