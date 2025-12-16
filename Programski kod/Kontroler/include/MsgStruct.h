#pragma once
#include <Arduino.h>

struct msgStruct
{
    // 0 stop, 1 forward, -1 backward
    int8_t moveDirection = 0;

    // 0 no rotation, 1 right, -1 left
    int8_t rotation = 0;

    // 0 to 4095
    uint16_t speed = 2048;
};

bool operator!=( const msgStruct& a, const msgStruct& b );