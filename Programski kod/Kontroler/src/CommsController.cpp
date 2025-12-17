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

esp_err_t CommsController::sendMessage( const msgStruct* outgoingMessage )
{
    lastTimeMsgSent = millis();

    return esp_now_send( macAdressRobotCar, ( uint8_t* ) outgoingMessage, sizeof( *outgoingMessage ) );
}
