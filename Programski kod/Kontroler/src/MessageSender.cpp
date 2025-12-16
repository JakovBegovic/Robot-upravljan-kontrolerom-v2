#include "MessageSender.h"

esp_err_t MessageSender::setupWiFi()
{
    WiFi.mode( WIFI_STA );

    return esp_now_init();
}

esp_err_t MessageSender::setupEspNow()
{
    memcpy( espNowPeerInfo.peer_addr, macAdressRobotCar, 6 );
    espNowPeerInfo.channel = 0;
    espNowPeerInfo.encrypt = false;

    return esp_now_add_peer( &espNowPeerInfo );
}

esp_err_t MessageSender::setup()
{
    if(
        MessageSender::setupWiFi() == ESP_OK &&
        MessageSender::setupEspNow() == ESP_OK
    )
    {
        return ESP_OK;
    }
    else
    {
        return ESP_FAIL;
    }
}

esp_err_t MessageSender::sendMessage( const msgStruct* outgoingMessage )
{
    lastTimeMsgSent = millis();

    return esp_now_send( macAdressRobotCar, ( uint8_t* ) outgoingMessage, sizeof( *outgoingMessage ) );
}
