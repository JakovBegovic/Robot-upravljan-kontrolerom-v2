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


public:
    msgStruct constructedMsg;
    unsigned long lastTimeMsgSent = 0;

    msgStruct lastMessageSent;
    uint8_t failedMsgsInARow = 0;


private:
    esp_err_t setupWiFi();
    esp_err_t setupEspNow();

public:
    esp_err_t setup();

    void constructMsg( HardwareReader hrdwrReader );

    /**
     * @brief   Checks conditions for sending message over ESP NOW protocol
     *
     * @returns
     *          true : conditions for sending message are met
     *          false : conditions for sending message are not met
     */
    bool shouldSendMsg();

    /**
     * @brief   Send message using ESP NOW protocol
     */
    esp_err_t sendMessage( const msgStruct *outgoingMessage );
};
