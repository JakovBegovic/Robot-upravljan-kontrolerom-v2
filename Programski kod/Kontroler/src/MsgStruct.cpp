#include "msgStruct.h"

bool operator!=( const msgStruct& a, const msgStruct& b )
{
    return a.moveDirection != b.moveDirection ||
           a.rotation != b.rotation ||
           !(
               a.speed - 200 <= b.speed &&
               a.speed + 200 >= b.speed
           );
}

void copyMsg( msgStruct& from, msgStruct& to )
{
    to.moveDirection = from.moveDirection;
    to.rotation = from.rotation;
    to.speed = from.speed;
}