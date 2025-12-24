#include "HrdwrController.h"

namespace
{
    /*
    *   HrdwrController private variables
    */
    const uint8_t buzzerPIN = 25;


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

    xTaskCreatePinnedToCore(
        playSong, // Task function
        "playSong", // Task name
        1000, // Stack size
        NULL, // Parameters
        2, // Priority
        NULL, // Task handle (optional)
        1 // Core ID
    );
}

void HrdwrController::playSong( void *pvParameter )
{
    int size = doomDurationsSize;

    for ( int note = 0; note < size; note++ )
    {
        //quarter note = 1 sec / 4, eighth note = 1 sec / 8, etc.
        int duration = 1000 / doomDurations[ note ];
        tone( buzzerPIN, doomMelody[ note ], duration );

        //to distinguish the notes, set a minimum time between them.
        int pauseBetweenNotes = duration * 1.30;
        vTaskDelay( pauseBetweenNotes / portTICK_PERIOD_MS );

        //stop the tone playing:
        noTone( buzzerPIN );
    }
}
