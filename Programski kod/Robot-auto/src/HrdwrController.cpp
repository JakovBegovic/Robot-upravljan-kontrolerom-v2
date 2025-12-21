#include "HrdwrController.h"

namespace
{
    /*
    *   HrdwrController private variables
    */

    const uint8_t ledPINs[ 6 ] = { 12, 13, 14, 15, 23, 19 };
}

void HrdwrController::setup()
{
    for ( int i = 0; i < 6; i++ )
    {
        pinMode( ledPINs[ i ], OUTPUT );
    }

    controlLEDs( CommsController::getRecievedMsg().moveDirection, CommsController::getRecievedMsg().rotation );
}

void HrdwrController::controlLEDs( int8_t moveDirection, int8_t rotation )
{
    for ( int i = 0; i < 6; i++ )
    {
        digitalWrite( ledPINs[ i ], LOW );
    }

    digitalWrite( ledPINs[ 1 + moveDirection ], HIGH );

    digitalWrite( ledPINs[ 4 + rotation ], HIGH );
}
