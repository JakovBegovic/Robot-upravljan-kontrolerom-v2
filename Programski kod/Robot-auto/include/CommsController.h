#pragma once
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include "msgStruct.h"
#include "HrdwrController.h"

namespace CommsController
{
    /*
    *   CommsController public functions
    */

    msgStruct getRecievedMsg();

    unsigned long getLastTimeRcvdMsg();

    void setRecievedMsg( int8_t moveDirection,
                         int8_t rotation,
                         uint16_t speed );

    esp_err_t setup();

    void onDataRecieved( const uint8_t * macAddress, const uint8_t *recievedData, int length );

}