#include "HrdwrReader.h"

namespace
{
    /*
    *   HrdwrReader private variables
    */

    // forward, backward, right, left, music
    const uint8_t btnPINs[ 5 ] = { 12, 13, 14, 15, 23 };
    const uint8_t potentioPIN = 35;

    unsigned long lastInterrupt = 0;


    /*
    *   HrdwrReader private functions
    */

    void musicCtrl( void *pvParameter )
    {
        bool isMusicBtnPressed = false;
        uint16_t pressedInRow = 0;

        while( true )
        {
            isMusicBtnPressed = !digitalRead( btnPINs[ 4 ] );

            if( isMusicBtnPressed )
            {
                pressedInRow++;

                if( pressedInRow == 25 )
                {
                    HrdwrController::pauseMusic();
                }
            }
            else
            {
                if( pressedInRow > 0
                    &&
                    pressedInRow < 15
                  )
                {
                    HrdwrController::playNextSong();
                }

                pressedInRow = 0;
            }

            vTaskDelay( 75 / portTICK_PERIOD_MS );
        }
    }


    void setupMusicCtrl()
    {
        xTaskCreatePinnedToCore(
            musicCtrl, // Task function
            "musicCtrl", // Task name
            1024, // Stack size
            NULL, // Parameters
            2, // Priority
            NULL, // Task handle
            1 // Core ID
        );
    }

    void setupBTNs()
    {
        for ( int i = 0; i < sizeof( btnPINs ) / sizeof( uint8_t ); i++ )
        {
            pinMode( btnPINs[ i ], INPUT_PULLUP );
        }
    }

    void setupADC()
    {
        analogReadResolution( 12 );
    }
}


/*
*   HrdwrReader public function definitions
*/

void HrdwrReader::setup()
{
    setupBTNs();
    setupMusicCtrl();
    setupADC();
}

int8_t HrdwrReader::getMoveDir()
{
    return !digitalRead( btnPINs[ 0 ] ) - !digitalRead( btnPINs[ 1 ] );
}

int8_t HrdwrReader::getRotation()
{
    return !digitalRead( btnPINs[ 2 ] ) - !digitalRead( btnPINs[ 3 ] );
}

uint16_t HrdwrReader::getSpeed()
{
    return analogRead( potentioPIN );
}
