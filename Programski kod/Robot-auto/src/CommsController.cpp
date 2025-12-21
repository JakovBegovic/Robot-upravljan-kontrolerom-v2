#include "CommsController.h"

namespace
{
    /*
    *   CommsController private variables
    */

    const uint8_t macAdressRobotCar[] = { 0x7C, 0x87, 0xCE, 0xF8, 0xCA, 0xE8 };
    const uint8_t macAdressController[] = { 0x94, 0xE6, 0x86, 0xA8, 0x61, 0x24 };

    esp_now_peer_info_t espNowPeerInfo;

    msgStruct recievedMsg;

    unsigned long lastTimeRcvdMsg;


    /*
    *   CommsController private functions
    */

    void setupDefalutMsgValues()
    {
        lastTimeRcvdMsg = 0;

        recievedMsg.moveDirection = 0;
        recievedMsg.rotation = 0;
        recievedMsg.speed = 2047;
    }

    esp_err_t setupWiFi()
    {
        WiFi.mode( WIFI_STA );

        return esp_now_init();
    }

    esp_err_t setupEspNow()
    {
        memcpy( espNowPeerInfo.peer_addr, macAdressController, 6 );
        espNowPeerInfo.channel = 0;
        espNowPeerInfo.encrypt = false;

        return esp_now_add_peer(&espNowPeerInfo );
    }
}


/*
* CommsController public function definitions
*/

msgStruct CommsController::getRecievedMsg()
{
    return recievedMsg;
}

unsigned long CommsController::getLastTimeRcvdMsg()
{
    return lastTimeRcvdMsg;
}

void CommsController::setRecievedMsg( int8_t moveDirection, int8_t rotation, uint16_t speed )
{
    recievedMsg.moveDirection = moveDirection;
    recievedMsg.rotation = rotation;
    recievedMsg.speed = speed;
}

esp_err_t CommsController::setup()
{
    setupDefalutMsgValues();

    esp_err_t resultSetupWiFi = setupWiFi();
    esp_err_t resultSetupEspNow = setupEspNow();
    esp_err_t resultRegisterRecievCb = esp_now_register_recv_cb( onDataRecieved );

    if ( resultSetupWiFi + resultSetupEspNow + resultRegisterRecievCb == ESP_OK )
    {
        return ESP_OK;
    }
    else
    {
        return ESP_FAIL;
    }
}

void CommsController::onDataRecieved( const uint8_t *macAddress, const uint8_t *recievedData, int length )
{
    memcpy( &recievedMsg, recievedData, sizeof( recievedMsg ) );

    lastTimeRcvdMsg = millis();

    HrdwrController::controlLEDs( recievedMsg );
}