#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "MsgStruct.h"
#include "HardwareReader.h"

class CommsController
{
private:
    const uint8_t macAdressRobotCar[ 6 ] = { 0x7C, 0x87, 0xCE, 0xF8, 0xCA, 0xE8 };
    const uint8_t macAdressController[ 6 ] = { 0x94, 0xE6, 0x86, 0xA8, 0x61, 0x24 };

    esp_now_peer_info_t espNowPeerInfo;

    unsigned long lastTimeMsgSent = 0;
    msgStruct lastMessageSent;
    msgStruct constructedMsg;

public:
    uint8_t failedMsgsInARow = 0;


private:
    esp_err_t setupWiFi();
    esp_err_t setupEspNow();

    bool shouldSendUpdateMsg();
    bool shouldSendRenewMsg();
    bool shouldSendReconnectMsg();

    void confirmSuccessfulSend();

public:

    msgStruct getConstructedMsg();

    esp_err_t setup();

    /**
     * @brief   Construct message from user input to be sent using ESP NOW protocol
     */
    void constructMsg( HardwareReader hrdwrReader );

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
};
