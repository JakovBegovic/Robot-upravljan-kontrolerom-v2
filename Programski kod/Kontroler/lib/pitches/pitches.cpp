#include "pitches.h"


namespace
{
    static constexpr int superMario[] =
    {
        // Super Mario Bros theme
        // Score available at https://musescore.com/user/2123/scores/2145
        // Theme by Koji Kondo

        NOTE_E5, 8, NOTE_E5, 8, REST, 8, NOTE_E5, 8, REST, 8, NOTE_C5, 8, NOTE_E5, 8, //1
        NOTE_G5, 4, REST, 4, NOTE_G4, 8, REST, 4,
        NOTE_C5, -4, NOTE_G4, 8, REST, 4, NOTE_E4, -4, // 3
        NOTE_A4, 4, NOTE_B4, 4, NOTE_AS4, 8, NOTE_A4, 4,
        NOTE_G4, -8, NOTE_E5, -8, NOTE_G5, -8, NOTE_A5, 4, NOTE_F5, 8, NOTE_G5, 8,
        REST, 8, NOTE_E5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_B4, -4,
        NOTE_C5, -4, NOTE_G4, 8, REST, 4, NOTE_E4, -4, // repeats from 3
        NOTE_A4, 4, NOTE_B4, 4, NOTE_AS4, 8, NOTE_A4, 4,
        NOTE_G4, -8, NOTE_E5, -8, NOTE_G5, -8, NOTE_A5, 4, NOTE_F5, 8, NOTE_G5, 8,
        REST, 8, NOTE_E5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_B4, -4,


        REST, 4, NOTE_G5, 8, NOTE_FS5, 8, NOTE_F5, 8, NOTE_DS5, 4, NOTE_E5, 8, //7
        REST, 8, NOTE_GS4, 8, NOTE_A4, 8, NOTE_C4, 8, REST, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_D5, 8,
        REST, 4, NOTE_DS5, 4, REST, 8, NOTE_D5, -4,
        NOTE_C5, 2, REST, 2,

        REST, 4, NOTE_G5, 8, NOTE_FS5, 8, NOTE_F5, 8, NOTE_DS5, 4, NOTE_E5, 8, //repeats from 7
        REST, 8, NOTE_GS4, 8, NOTE_A4, 8, NOTE_C4, 8, REST, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_D5, 8,
        REST, 4, NOTE_DS5, 4, REST, 8, NOTE_D5, -4,
        NOTE_C5, 2, REST, 2,

        NOTE_C5, 8, NOTE_C5, 4, NOTE_C5, 8, REST, 8, NOTE_C5, 8, NOTE_D5, 4, //11
        NOTE_E5, 8, NOTE_C5, 4, NOTE_A4, 8, NOTE_G4, 2,

        NOTE_C5, 8, NOTE_C5, 4, NOTE_C5, 8, REST, 8, NOTE_C5, 8, NOTE_D5, 8, NOTE_E5, 8, //13
        REST, 1,
        NOTE_C5, 8, NOTE_C5, 4, NOTE_C5, 8, REST, 8, NOTE_C5, 8, NOTE_D5, 4,
        NOTE_E5, 8, NOTE_C5, 4, NOTE_A4, 8, NOTE_G4, 2,
        NOTE_E5, 8, NOTE_E5, 8, REST, 8, NOTE_E5, 8, REST, 8, NOTE_C5, 8, NOTE_E5, 4,
        NOTE_G5, 4, REST, 4, NOTE_G4, 4, REST, 4,
        NOTE_C5, -4, NOTE_G4, 8, REST, 4, NOTE_E4, -4, // 19

        NOTE_A4, 4, NOTE_B4, 4, NOTE_AS4, 8, NOTE_A4, 4,
        NOTE_G4, -8, NOTE_E5, -8, NOTE_G5, -8, NOTE_A5, 4, NOTE_F5, 8, NOTE_G5, 8,
        REST, 8, NOTE_E5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_B4, -4,

        NOTE_C5, -4, NOTE_G4, 8, REST, 4, NOTE_E4, -4, // repeats from 19
        NOTE_A4, 4, NOTE_B4, 4, NOTE_AS4, 8, NOTE_A4, 4,
        NOTE_G4, -8, NOTE_E5, -8, NOTE_G5, -8, NOTE_A5, 4, NOTE_F5, 8, NOTE_G5, 8,
        REST, 8, NOTE_E5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_B4, -4,

        NOTE_E5, 8, NOTE_C5, 4, NOTE_G4, 8, REST, 4, NOTE_GS4, 4, //23
        NOTE_A4, 8, NOTE_F5, 4, NOTE_F5, 8, NOTE_A4, 2,
        NOTE_D5, -8, NOTE_A5, -8, NOTE_A5, -8, NOTE_A5, -8, NOTE_G5, -8, NOTE_F5, -8,

        NOTE_E5, 8, NOTE_C5, 4, NOTE_A4, 8, NOTE_G4, 2, //26
        NOTE_E5, 8, NOTE_C5, 4, NOTE_G4, 8, REST, 4, NOTE_GS4, 4,
        NOTE_A4, 8, NOTE_F5, 4, NOTE_F5, 8, NOTE_A4, 2,
        NOTE_B4, 8, NOTE_F5, 4, NOTE_F5, 8, NOTE_F5, -8, NOTE_E5, -8, NOTE_D5, -8,
        NOTE_C5, 8, NOTE_E4, 4, NOTE_E4, 8, NOTE_C4, 2,

        NOTE_E5, 8, NOTE_C5, 4, NOTE_G4, 8, REST, 4, NOTE_GS4, 4, //repeats from 23
        NOTE_A4, 8, NOTE_F5, 4, NOTE_F5, 8, NOTE_A4, 2,
        NOTE_D5, -8, NOTE_A5, -8, NOTE_A5, -8, NOTE_A5, -8, NOTE_G5, -8, NOTE_F5, -8,

        NOTE_E5, 8, NOTE_C5, 4, NOTE_A4, 8, NOTE_G4, 2, //26
        NOTE_E5, 8, NOTE_C5, 4, NOTE_G4, 8, REST, 4, NOTE_GS4, 4,
        NOTE_A4, 8, NOTE_F5, 4, NOTE_F5, 8, NOTE_A4, 2,
        NOTE_B4, 8, NOTE_F5, 4, NOTE_F5, 8, NOTE_F5, -8, NOTE_E5, -8, NOTE_D5, -8,
        NOTE_C5, 8, NOTE_E4, 4, NOTE_E4, 8, NOTE_C4, 2,
        NOTE_C5, 8, NOTE_C5, 4, NOTE_C5, 8, REST, 8, NOTE_C5, 8, NOTE_D5, 8, NOTE_E5, 8,
        REST, 1,

        NOTE_C5, 8, NOTE_C5, 4, NOTE_C5, 8, REST, 8, NOTE_C5, 8, NOTE_D5, 4, //33
        NOTE_E5, 8, NOTE_C5, 4, NOTE_A4, 8, NOTE_G4, 2,
        NOTE_E5, 8, NOTE_E5, 8, REST, 8, NOTE_E5, 8, REST, 8, NOTE_C5, 8, NOTE_E5, 4,
        NOTE_G5, 4, REST, 4, NOTE_G4, 4, REST, 4,
        NOTE_E5, 8, NOTE_C5, 4, NOTE_G4, 8, REST, 4, NOTE_GS4, 4,
        NOTE_A4, 8, NOTE_F5, 4, NOTE_F5, 8, NOTE_A4, 2,
        NOTE_D5, -8, NOTE_A5, -8, NOTE_A5, -8, NOTE_A5, -8, NOTE_G5, -8, NOTE_F5, -8,

        NOTE_E5, 8, NOTE_C5, 4, NOTE_A4, 8, NOTE_G4, 2, //40
        NOTE_E5, 8, NOTE_C5, 4, NOTE_G4, 8, REST, 4, NOTE_GS4, 4,
        NOTE_A4, 8, NOTE_F5, 4, NOTE_F5, 8, NOTE_A4, 2,
        NOTE_B4, 8, NOTE_F5, 4, NOTE_F5, 8, NOTE_F5, -8, NOTE_E5, -8, NOTE_D5, -8,
        NOTE_C5, 8, NOTE_E4, 4, NOTE_E4, 8, NOTE_C4, 2,

        //game over sound
        NOTE_C5, -4, NOTE_G4, -4, NOTE_E4, 4, //45
        NOTE_A4, -8, NOTE_B4, -8, NOTE_A4, -8, NOTE_GS4, -8, NOTE_AS4, -8, NOTE_GS4, -8,
        NOTE_G4, 8, NOTE_D4, 8, NOTE_E4, -2,
    };

    static constexpr int doom[] =
    {
        // At Doom's Gate (E1M1)
        // Score available at https://musescore.com/pieridot/doom

        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //1
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //5
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //9
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //13
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
        NOTE_FS3, -16, NOTE_D3, -16, NOTE_B2, -16, NOTE_A3, -16, NOTE_FS3, -16, NOTE_B2, -16, NOTE_D3, -16, NOTE_FS3, -16, NOTE_A3, -16, NOTE_FS3, -16, NOTE_D3, -16, NOTE_B2, -16,

        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //17
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //21
        NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
        NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
        NOTE_B3, -16, NOTE_G3, -16, NOTE_E3, -16, NOTE_G3, -16, NOTE_B3, -16, NOTE_E4, -16, NOTE_G3, -16, NOTE_B3, -16, NOTE_E4, -16, NOTE_B3, -16, NOTE_G4, -16, NOTE_B4, -16,

        NOTE_A2, 8, NOTE_A2, 8, NOTE_A3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_G3, 8, NOTE_A2, 8, NOTE_A2, 8, //25
        NOTE_F3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_DS3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_E3, 8, NOTE_F3, 8,
        NOTE_A2, 8, NOTE_A2, 8, NOTE_A3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_G3, 8, NOTE_A2, 8, NOTE_A2, 8,
        NOTE_F3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_DS3, -2,

        NOTE_A2, 8, NOTE_A2, 8, NOTE_A3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_G3, 8, NOTE_A2, 8, NOTE_A2, 8, //29
        NOTE_F3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_DS3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_E3, 8, NOTE_F3, 8,
        NOTE_A2, 8, NOTE_A2, 8, NOTE_A3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_G3, 8, NOTE_A2, 8, NOTE_A2, 8,
        NOTE_A3, -16, NOTE_F3, -16, NOTE_D3, -16, NOTE_A3, -16, NOTE_F3, -16, NOTE_D3, -16, NOTE_C4, -16, NOTE_A3, -16, NOTE_F3, -16, NOTE_A3, -16, NOTE_F3, -16, NOTE_D3, -16,
    };

    static constexpr int pacman[] =
    {
        // Pacman
        // Score available at https://musescore.com/user/85429/scores/107109
        NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
        NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
        NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

        NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_B5, 32, //2
        NOTE_FS5, -16, NOTE_DS5, 8, NOTE_DS5, 32, NOTE_E5, 32, NOTE_F5, 32,
        NOTE_F5, 32, NOTE_FS5, 32, NOTE_G5, 32, NOTE_G5, 32, NOTE_GS5, 32, NOTE_A5, 16, NOTE_B5, 8
    };

    static constexpr int tetris[] =
    {
        //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192

        NOTE_E5, 4, NOTE_B4, 8, NOTE_C5, 8, NOTE_D5, 4, NOTE_C5, 8, NOTE_B4, 8,
        NOTE_A4, 4, NOTE_A4, 8, NOTE_C5, 8, NOTE_E5, 4, NOTE_D5, 8, NOTE_C5, 8,
        NOTE_B4, -4, NOTE_C5, 8, NOTE_D5, 4, NOTE_E5, 4,
        NOTE_C5, 4, NOTE_A4, 4, NOTE_A4, 4, REST, 4,

        REST, 8, NOTE_D5, 4, NOTE_F5, 8, NOTE_A5, 4, NOTE_G5, 8, NOTE_F5, 8,
        NOTE_E5, -4, NOTE_C5, 8, NOTE_E5, 4, NOTE_D5, 8, NOTE_C5, 8,
        NOTE_B4, 4, NOTE_B4, 8, NOTE_C5, 8, NOTE_D5, 4, NOTE_E5, 4,
        NOTE_C5, 4, NOTE_A4, 4, NOTE_A4, 4, REST, 4,

        NOTE_E5, 2, NOTE_C5, 2,
        NOTE_D5, 2, NOTE_B4, 2,
        NOTE_C5, 2, NOTE_A4, 2,
        NOTE_B4, 1,

        NOTE_E5, 2, NOTE_C5, 2,
        NOTE_D5, 2, NOTE_B4, 2,
        NOTE_C5, 4, NOTE_E5, 4, NOTE_A5, 2,
        NOTE_GS5, 1,

        NOTE_E5, 4, NOTE_B4, 8, NOTE_C5, 8, NOTE_D5, 4, NOTE_C5, 8, NOTE_B4, 8,
        NOTE_A4, 4, NOTE_A4, 8, NOTE_C5, 8, NOTE_E5, 4, NOTE_D5, 8, NOTE_C5, 8,
        NOTE_B4, -4, NOTE_C5, 8, NOTE_D5, 4, NOTE_E5, 4,
        NOTE_C5, 4, NOTE_A4, 4, NOTE_A4, 4, REST, 4,

        REST, 8, NOTE_D5, 4, NOTE_F5, 8, NOTE_A5, 4, NOTE_G5, 8, NOTE_F5, 8,
        REST, 8, NOTE_E5, 4, NOTE_C5, 8, NOTE_E5, 4, NOTE_D5, 8, NOTE_C5, 8,
        REST, 8, NOTE_B4, 4, NOTE_C5, 8, NOTE_D5, 4, NOTE_E5, 4,
        REST, 8, NOTE_C5, 4, NOTE_A4, 8, NOTE_A4, 4, REST, 4,
    };

    static constexpr int miichannel[] =
    {

        // Mii Channel theme
        // Score available at https://musescore.com/user/16403456/scores/4984153
        // Uploaded by Catalina Andrade

        NOTE_FS4, 8, REST, 8, NOTE_A4, 8, NOTE_CS5, 8, REST, 8, NOTE_A4, 8, REST, 8, NOTE_FS4, 8, //1
        NOTE_D4, 8, NOTE_D4, 8, NOTE_D4, 8, REST, 8, REST, 4, REST, 8, NOTE_CS4, 8,
        NOTE_D4, 8, NOTE_FS4, 8, NOTE_A4, 8, NOTE_CS5, 8, REST, 8, NOTE_A4, 8, REST, 8, NOTE_F4, 8,
        NOTE_E5, -4, NOTE_DS5, 8, NOTE_D5, 8, REST, 8, REST, 4,

        NOTE_GS4, 8, REST, 8, NOTE_CS5, 8, NOTE_FS4, 8, REST, 8, NOTE_CS5, 8, REST, 8, NOTE_GS4, 8, //5
        REST, 8, NOTE_CS5, 8, NOTE_G4, 8, NOTE_FS4, 8, REST, 8, NOTE_E4, 8, REST, 8,
        NOTE_E4, 8, NOTE_E4, 8, NOTE_E4, 8, REST, 8, REST, 4, NOTE_E4, 8, NOTE_E4, 8,
        NOTE_E4, 8, REST, 8, REST, 4, NOTE_DS4, 8, NOTE_D4, 8,

        NOTE_CS4, 8, REST, 8, NOTE_A4, 8, NOTE_CS5, 8, REST, 8, NOTE_A4, 8, REST, 8, NOTE_FS4, 8, //9
        NOTE_D4, 8, NOTE_D4, 8, NOTE_D4, 8, REST, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_E5, 8, REST, 8,
        REST, 8, NOTE_FS4, 8, NOTE_A4, 8, NOTE_CS5, 8, REST, 8, NOTE_A4, 8, REST, 8, NOTE_F4, 8,
        NOTE_E5, 2, NOTE_D5, 8, REST, 8, REST, 4,

        NOTE_B4, 8, NOTE_G4, 8, NOTE_D4, 8, NOTE_CS4, 4, NOTE_B4, 8, NOTE_G4, 8, NOTE_CS4, 8, //13
        NOTE_A4, 8, NOTE_FS4, 8, NOTE_C4, 8, NOTE_B3, 4, NOTE_F4, 8, NOTE_D4, 8, NOTE_B3, 8,
        NOTE_E4, 8, NOTE_E4, 8, NOTE_E4, 8, REST, 4, REST, 4, NOTE_AS4, 4,
        NOTE_CS5, 8, NOTE_D5, 8, NOTE_FS5, 8, NOTE_A5, 8, REST, 8, REST, 4,

        REST, 2, NOTE_A3, 4, NOTE_AS3, 4, //17
        NOTE_A3, -4, NOTE_A3, 8, NOTE_A3, 2,
        REST, 4, NOTE_A3, 8, NOTE_AS3, 8, NOTE_A3, 8, NOTE_F4, 4, NOTE_C4, 8,
        NOTE_A3, -4, NOTE_A3, 8, NOTE_A3, 2,

        REST, 2, NOTE_B3, 4, NOTE_C4, 4, //21
        NOTE_CS4, -4, NOTE_C4, 8, NOTE_CS4, 2,
        REST, 4, NOTE_CS4, 8, NOTE_C4, 8, NOTE_CS4, 8, NOTE_GS4, 4, NOTE_DS4, 8,
        NOTE_CS4, -4, NOTE_DS4, 8, NOTE_B3, 1,

        NOTE_E4, 4, NOTE_E4, 4, NOTE_E4, 4, REST, 8, //25
    };
}

const songInfoStruct songs[] =
{
    { pacman, sizeof( pacman ) / sizeof( pacman[ 0 ] ), 105 },
    { superMario, sizeof( superMario ) / sizeof( superMario[ 0 ] ), 200 },
    { tetris, sizeof( tetris ) / sizeof( tetris[ 0 ] ), 144 },
    { doom, sizeof( doom ) / sizeof( doom[ 0 ] ), 225 },
    { miichannel, sizeof( miichannel ) / sizeof( miichannel[ 0 ] ), 114 },
};

const std::size_t songsCount = sizeof( songs ) / sizeof( songs[ 0 ] );

