#include "HrdwrController.h"

namespace
{
    /*
    *   HrdwrController private variables
    */
    const uint8_t buzzerPIN = 25;

    uint8_t songPlaying = 0;

    QueueHandle_t musicQueue = NULL;
    TaskHandle_t musicTask = NULL;

    /*
    *   HrdwrController private functions
    */

    void pauseMusic()
    {
        vTaskSuspend( musicTask );
    }

    void resumeMusic()
    {
        vTaskResume( musicTask );
    }

    bool musicIsPaused()
    {
        return eTaskGetState( musicTask ) == eSuspended;
    }

    void playNextSong()
    {
        songPlaying = ( songPlaying + 1 ) % songsCount ;

        xQueueSend( musicQueue, &songPlaying, 0 );

        if( musicIsPaused() )
        {
            resumeMusic();
        }
    }

    void playSong( void *pvParameter )
    {
        uint8_t songNum = *( uint8_t * )pvParameter;

        while( true )
        {
            int tempo = songs[ songNum ].tempo;
            int notes = songs[ songNum ].length / 2;
            int wholenote = ( 60000 * 4 ) / tempo; // in ms
            int divider = 0, noteDuration = 0;

            for ( int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2 )
            {
                if( xQueueReceive( musicQueue, &songNum, 0 ) != errQUEUE_EMPTY )
                {
                    break;
                }

                divider = songs[ songNum ].data[ thisNote + 1 ];

                if ( divider > 0 )
                {
                    noteDuration = ( wholenote ) / divider;
                }
                else if ( divider < 0 )
                {
                    // dotted notes are represented with negative durations
                    noteDuration = ( wholenote ) / abs( divider );
                    noteDuration *= 1.5; // increases the duration for dotted notes
                }

                // play the note for 90% of the duration
                tone( buzzerPIN, songs[ songNum ].data[ thisNote ], noteDuration * 0.9 );
                vTaskDelay( noteDuration / portTICK_PERIOD_MS );

                // stop the waveform generation before the next note.
                noTone( buzzerPIN );
            }
        }
    }

    void setupSongPlayer()
    {
        pinMode( buzzerPIN, OUTPUT );

        musicQueue = xQueueCreate( 5, sizeof( uint8_t ) );

        xTaskCreatePinnedToCore(
            playSong, // Task function
            "playSong", // Task name
            2048, // Stack size
            ( void * )&songPlaying, // Parameters
            2, // Priority
            &musicTask, // Task handle
            1 // Core ID
        );

        pauseMusic();
    }

    void musicCtrl( void *pvParameter )
    {
        bool isMusicBtnPressed = false;
        uint16_t pressedInRow = 0;

        while( true )
        {
            isMusicBtnPressed = HrdwrReader::readMusicBtn();

            if( isMusicBtnPressed )
            {
                pressedInRow++;

                if( pressedInRow == 25 )
                {
                    pauseMusic();
                }
            }
            else
            {
                if( pressedInRow > 0
                    &&
                    pressedInRow < 15
                  )
                {
                    if( musicIsPaused() )
                    {
                        resumeMusic();
                    }
                    else
                    {
                        playNextSong();
                    }
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
}


/*
*   HrdwrController public function definitions
*/

void HrdwrController::setup()
{
    setupSongPlayer();
    setupMusicCtrl();
}
