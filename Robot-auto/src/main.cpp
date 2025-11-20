#include <Arduino.h>

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