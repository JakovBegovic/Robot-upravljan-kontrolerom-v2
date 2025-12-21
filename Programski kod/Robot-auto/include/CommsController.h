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

    /**
    * @brief   Getter for recievedMsg variable
    */
    msgStruct getRecievedMsg();

    /**
    * @brief   Getter for lastTimeRcvdMsg variable
    */
    unsigned long getLastTimeRcvdMsg();

    /**
    * @brief   Setter for lastTimeRcvdMsg variable
    */
    void setRecievedMsg( int8_t moveDirection,
                         int8_t rotation,
                         uint16_t speed );

    /**
    * @brief   Enable and setup ESP NOW communication
    */
    esp_err_t setup();

    /**
    * @brief   Callback function called on recieved packet from controller
    */
    void onDataRecieved( const uint8_t * macAddress, const uint8_t *recievedData, int length );

}