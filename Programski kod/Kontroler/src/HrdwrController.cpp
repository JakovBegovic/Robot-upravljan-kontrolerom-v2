#include "HrdwrController.h"

namespace
{
    /*
    *   HrdwrController private variables
    */
    const uint8_t buzzerPIN = 25;

    uint8_t songPlaying;

    QueueHandle_t musicQueue = NULL;

    /*
    *   HrdwrController private functions
    */
}


/*
*   HrdwrController public function definitions
*/

void HrdwrController::setup()
{
    pinMode( buzzerPIN, OUTPUT );

    songPlaying = 0;

    musicQueue = xQueueCreate( 5, sizeof( uint8_t ) );

    xTaskCreatePinnedToCore(
        playSong, // Task function
        "playSong", // Task name
        2048, // Stack size
        ( void * )&songPlaying, // Parameters
        2, // Priority
        NULL, // Task handle (optional)
        1 // Core ID
    );
}

void HrdwrController::playSong( void *pvParameter )
{
    uint8_t songNum = *( uint8_t * )pvParameter;

    while( true )
    {
        int size = songSizes[ songNum ];

        for ( int note = 0; note < size; note++ )
        {
            //quarter note = 1 sec / 4, eighth note = 1 sec / 8, etc.
            int duration = 1000 / songDurations[ songNum ][ note ];
            tone( buzzerPIN, songMelodies[ songNum ][ note ], duration );

            //to distinguish the notes, set a minimum time between them.
            int pauseBetweenNotes = duration * 1.30;
            vTaskDelay( pauseBetweenNotes / portTICK_PERIOD_MS );

            //stop the tone playing:
            noTone( buzzerPIN );

            if( xQueueReceive( musicQueue, &songNum, 0 ) != errQUEUE_EMPTY )
            {
                break;
            }
        }
    }
}

void HrdwrController::playNextSong()
{
    songPlaying = ( songPlaying + 1 ) % 2;

    xQueueSend( musicQueue, &songPlaying, 0 );
}

