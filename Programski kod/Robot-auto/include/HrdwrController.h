#pragma once
#include <Arduino.h>

#include "CommsController.h"


namespace HrdwrController
{
    /*
    *   HrdwrController public functions
    */

    void setup();

    void controlLEDs( int8_t moveDirection, int8_t rotation );
}