#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "HardwareReader.h"
#include "MessageSender.h"
#include "MsgStruct.h"

#define DEBUG 0

HardwareReader hardwareReader;

MessageSender messageSender;

void constructMsg( msgStruct* msgToConstruct );


uint8_t failedMsgsInARow = 0;


void onDataSent( const uint8_t* macAddress, esp_now_send_status_t status );



void setup()
{
    if( DEBUG )
    {
        Serial.begin( 115200 );
    }

    hardwareReader.setup();

    messageSender.setup();

    esp_now_register_send_cb( onDataSent );
}

void loop()
{
    static msgStruct messageToSend;
    static msgStruct lastMessageSent;

    constructMsg( &messageToSend );

    esp_err_t result;

    if( (
            (
                messageToSend != lastMessageSent ||
                failedMsgsInARow > 0 &&
                failedMsgsInARow < 20
            )
            &&
            millis() - messageSender.lastTimeMsgSent > 50
        )
        ||
        (
            (
                messageToSend.moveDirection != 0 ||
                messageToSend.rotation != 0
            )
            &&
            millis() - messageSender.lastTimeMsgSent > 500
        )
      )
    {
        result = messageSender.sendMessage( &messageToSend );

        if( DEBUG )
        {
            Serial.print( "Sent " );
            Serial.print( messageToSend.speed );
            Serial.print( "   time: " );
            Serial.println( ( double )millis() / 1000 );
        }

        if( result == ESP_OK )
        {
            lastMessageSent.moveDirection = messageToSend.moveDirection;
            lastMessageSent.rotation = messageToSend.rotation;
            lastMessageSent.speed = messageToSend.speed;
        }
    }
}

void constructMsg( msgStruct* msgToConstruct )
{
    msgToConstruct->moveDirection = hardwareReader.getMoveDir();
    msgToConstruct->rotation = hardwareReader.getRotation();
    msgToConstruct->speed = hardwareReader.getSpeed();
}

void onDataSent( const uint8_t* macAddress, esp_now_send_status_t status )
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