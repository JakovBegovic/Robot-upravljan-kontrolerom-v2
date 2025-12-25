#include "HrdwrController.h"

namespace
{
    /*
    *   HrdwrController private variables
    */
    const uint8_t buzzerPIN = 25;

    uint8_t songPlaying;

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

    playNextSong();
}

void HrdwrController::playSong( void *pvParameter )
{
    while( true )
    {
        uint8_t songNum = *( uint8_t * )pvParameter;

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
        }
    }
}

void HrdwrController::playNextSong()
{
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
