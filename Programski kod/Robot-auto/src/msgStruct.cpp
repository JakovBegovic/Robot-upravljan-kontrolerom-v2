#include "msgStruct.h"

bool operator!=( const msgStruct& a, const msgStruct& b )
{
    return a.moveDirection != b.moveDirection
           ||
           a.rotation != b.rotation
           ||
           !areSpeedsMatching( a.speed, b.speed, 50 );
}

bool areSpeedsMatching( uint16_t speed1, uint16_t speed2, uint16_t interval )
{
    uint16_t diff = speed1 > speed2 ? speed1 - speed2 : speed2 - speed1;

    return diff <= interval;
}

void copyMsg( msgStruct& from, msgStruct& to )
{
    to.moveDirection = from.moveDirection;
    to.rotation = from.rotation;
    to.speed = from.speed;
}