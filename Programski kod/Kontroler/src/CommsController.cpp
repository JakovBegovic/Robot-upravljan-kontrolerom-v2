#include "CommsController.h"

esp_err_t CommsController::setupWiFi()
{
    WiFi.mode( WIFI_STA );

    return esp_now_init();
}

esp_err_t CommsController::setupEspNow()
{
    memcpy( espNowPeerInfo.peer_addr, macAdressRobotCar, 6 );
    espNowPeerInfo.channel = 0;
    espNowPeerInfo.encrypt = false;

    return esp_now_add_peer( &espNowPeerInfo );
}

bool CommsController::shouldSendUpdateMsg()
{
    return millis() - lastTimeMsgSent > 50
           &&
           constructedMsg != lastMessageSent;
}

bool CommsController::shouldSendRenewMsg()
{
    return millis() - lastTimeMsgSent > 500 &&
           (
               constructedMsg.moveDirection != 0 ||
               constructedMsg.rotation != 0
           );
}

bool CommsController::shouldSendReconnectMsg()
{
    return millis() - lastTimeMsgSent > 50 &&
           (
               failedMsgsInARow > 0 &&
               failedMsgsInARow < 20
           );
}

esp_err_t CommsController::setup()
{
    if(
        CommsController::setupWiFi() == ESP_OK &&
        CommsController::setupEspNow() == ESP_OK
    )
    {
        return ESP_OK;
    }
    else
    {
        return ESP_FAIL;
    }
}

void CommsController::constructMsg( HardwareReader hrdwrReader )
{
    constructedMsg.moveDirection = hrdwrReader.getMoveDir();
    constructedMsg.rotation = hrdwrReader.getRotation();
    constructedMsg.speed = hrdwrReader.getSpeed();
}

bool CommsController::shouldSendMsg()
{
    return shouldSendUpdateMsg()
           ||
           shouldSendRenewMsg()
           ||
           shouldSendReconnectMsg();
}

esp_err_t CommsController::sendConstructedMessage()
{
    lastTimeMsgSent = millis();

    return esp_now_send( macAdressRobotCar, ( uint8_t* ) &constructedMsg, sizeof( constructedMsg ) );
}
