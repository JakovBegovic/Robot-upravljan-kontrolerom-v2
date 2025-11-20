#include <Arduino.h>

const int btnPINs[ 5 ] = {12, 13, 14, 15, 23};

void setup()
{
    Serial.begin( 115200 );

    for ( int i = 0; i < 5; i++ )
    {
        pinMode( btnPINs[ i ], INPUT_PULLUP );
    }

}

void loop()
{
    for ( int i = 0; i < 5; i++ )
    {
        if( !digitalRead( btnPINs[ i ] ) )
        {
            Serial.print( "Gumb " );
            Serial.print( i + 1 );
            Serial.print( " ukljucen!!\n" );
        }
    }

    delay( 200 );
}