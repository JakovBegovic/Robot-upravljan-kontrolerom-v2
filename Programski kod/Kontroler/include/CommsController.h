#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "msgStruct.h"
#include "HrdwrReader.h"

namespace CommsController
{
    /*
    *   CommsController public functions
    */

    /**
     * @brief   Getter for constructedMsg variable
     */
    msgStruct getConstructedMsg();

    uint8_t getMinTimeBetweenMsgs();

    /**
     * @brief   Enable and setup ESP NOW communication
     */
    esp_err_t setup();

    /**
     * @brief   Construct message from user input to be sent using ESP NOW protocol
     */
    void constructMsg();

    /**
     * @brief   Checks conditions for sending message over ESP NOW protocol
     *
     * @return
     *          true : conditions for sending message are met
     *          false : conditions for sending message are not met
     */
    bool shouldSendMsg();

    /**
     * @brief   Send message already constructed using ESP NOW protocol
     *
     * @return
     *          - ESP_OK : succeed
     *          - ESP_ERR_ESPNOW_NOT_INIT : ESPNOW is not initialized
     *          - ESP_ERR_ESPNOW_ARG : invalid argument
     *          - ESP_ERR_ESPNOW_FULL : peer list is full
     *          - ESP_ERR_ESPNOW_NO_MEM : out of memory
     *          - ESP_ERR_ESPNOW_EXIST : peer has existed
     */
    esp_err_t sendConstructedMsg();

    /**
     * @brief   Callback function called on recieved ACK packet from robot-car
     */
    void dataRecievedInfo( const uint8_t *macAddress, esp_now_send_status_t status );
};
