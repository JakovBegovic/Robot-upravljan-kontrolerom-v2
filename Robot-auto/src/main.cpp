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
    digitalWrite( ledPINs[ 0 ], HIGH );
    delay( 200 );
    digitalWrite( ledPINs[ 0 ], LOW );
    delay( 200 );
}