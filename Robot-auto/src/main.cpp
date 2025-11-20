#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>

const uint8_t macAdressRobotCar[] = {0x7C, 0x87, 0xCE, 0xF8, 0xCA, 0xE8};
const uint8_t macAdressController[] = {0x94, 0xE6, 0x86, 0xA8, 0x61, 0x24};

const int ledPINs[ 5 ] = {12, 13, 14, 15, 23};

void setup()
{
    Serial.begin( 115200 );

    for ( int i = 0; i < 5; i++ )
    {
        pinMode( ledPINs[ i ], OUTPUT );
    }
}

void loop()
{
    for ( int i = 0; i < 5; i++ )
    {
        digitalWrite( ledPINs[ i ], HIGH );
        digitalWrite( ledPINs[ ( i - 1 + 5 ) % 5 ], LOW );
        delay( 200 );
    }
}