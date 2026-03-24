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
    const float voltageDvsnInverse = 1.47f;
    const float adcToVoltageRatio = 0.000806f;

    const float batteryMaxVoltage = 4.25f;
    const float batteryMinVoltage = 3.1f;

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

float HrdwrReader::readBatteryVoltage()
{
    return ( float )analogRead( bttryReadPIN ) * adcToVoltageRatio * voltageDvsnInverse;
}

void HrdwrReader::readBttryVoltageTask( void *pvParameter )
{
    while( true )
    {
        float voltage = HrdwrReader::readBatteryVoltage();
        //Serial.println( voltage );

        vTaskDelay( 100 / portTICK_PERIOD_MS );
    }
}
