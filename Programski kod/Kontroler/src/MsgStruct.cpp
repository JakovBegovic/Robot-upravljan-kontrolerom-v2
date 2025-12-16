#include "MsgStruct.h"

bool operator!=( const msgStruct& a, const msgStruct& b )
{
    return a.moveDirection != b.moveDirection ||
           a.rotation != b.rotation ||
           !(
               a.speed - 200 <= b.speed &&
               a.speed + 200 >= b.speed
           );
}