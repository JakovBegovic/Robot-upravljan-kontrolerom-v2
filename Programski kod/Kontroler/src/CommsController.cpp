#include "CommsController.h"
#include "HardwareReader.h"

namespace
{
    /*
    *   CommsController private variables
    */

    const uint8_t macAdressRobotCar[ 6 ] = { 0x7C, 0x87, 0xCE, 0xF8, 0xCA, 0xE8 };
    const uint8_t macAdressController[ 6 ] = { 0x94, 0xE6, 0x86, 0xA8, 0x61, 0x24 };
    esp_now_peer_info_t espNowPeerInfo;

    msgStruct lastMsgSuccessfullySent;
    msgStruct constructedMsg;

    unsigned long lastTimeMsgSent = 0;

    uint8_t failedMsgsInARow = 0;


    /*
    *   CommsController private functions
    */

    esp_err_t setupWiFi()
    {
        WiFi.mode( WIFI_STA );

        return esp_now_init();
    }

    esp_err_t setupEspNow()
    {
        memcpy( espNowPeerInfo.peer_addr, macAdressRobotCar, 6 );
        espNowPeerInfo.channel = 0;
        espNowPeerInfo.encrypt = false;

        return esp_now_add_peer( &espNowPeerInfo );
    }

    bool shouldSendUpdateMsg()
    {
        return millis() - lastTimeMsgSent > 50
               &&
               constructedMsg != lastMsgSuccessfullySent;
    }

    bool shouldSendRenewMsg()
    {
        return millis() - lastTimeMsgSent > 500 &&
               (
                   constructedMsg.moveDirection != 0 ||
                   constructedMsg.rotation != 0
               );
    }

    bool shouldSendReconnectMsg()
    {
        return millis() - lastTimeMsgSent > 50 &&
               (
                   failedMsgsInARow > 0 &&
                   failedMsgsInARow < 20
               );
    }

    void confirmSuccessfulSend()
    {
        lastMsgSuccessfullySent.moveDirection = constructedMsg.moveDirection;
        lastMsgSuccessfullySent.rotation = constructedMsg.rotation;
        lastMsgSuccessfullySent.speed = constructedMsg.speed;
    }
}


/*
*   CommsController public function definitions
*/

msgStruct CommsController::getConstructedMsg()
{
    return constructedMsg;
}

esp_err_t CommsController::setup()
{
    esp_err_t resultSetupWiFi = setupWiFi();
    esp_err_t resultSetupEspNow = setupEspNow();
    esp_err_t resultRegisterSendCb = esp_now_register_send_cb( dataRecievedInfo );

    if ( resultSetupWiFi + resultSetupEspNow + resultRegisterSendCb == ESP_OK )
    {
        return ESP_OK;
    }
    else
    {
        return ESP_FAIL;
    }
}

void CommsController::constructMsg()
{
    constructedMsg.moveDirection = HardwareReader::getMoveDir();
    constructedMsg.rotation = HardwareReader::getRotation();
    constructedMsg.speed = HardwareReader::getSpeed();
}

bool CommsController::shouldSendMsg()
{
    return shouldSendUpdateMsg()
           ||
           shouldSendRenewMsg()
           ||
           shouldSendReconnectMsg();
}

esp_err_t CommsController::sendConstructedMsg()
{
    esp_err_t result = esp_now_send( macAdressRobotCar, ( uint8_t* ) &constructedMsg, sizeof( constructedMsg ) );

    lastTimeMsgSent = millis();

    if( result == ESP_OK )
    {
        confirmSuccessfulSend();
    }

    return result;
}

void CommsController::dataRecievedInfo( const uint8_t* macAddress, esp_now_send_status_t status )
{
    if( status == ESP_NOW_SEND_FAIL )
    {
        failedMsgsInARow++;
    }
    else
    {
        failedMsgsInARow = 0;
    }
}