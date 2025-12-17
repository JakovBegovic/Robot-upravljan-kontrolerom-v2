#include "HardwareReader.h"

void HardwareReader::setup()
{
    setupBTNs();
    setupADC();
}

int8_t HardwareReader::getMoveDir()
{
    return !digitalRead( btnPINs[ 0 ] ) - !digitalRead( btnPINs[ 1 ] );
}

int8_t HardwareReader::getRotation()
{
    return !digitalRead( btnPINs[ 2 ] ) - !digitalRead( btnPINs[ 3 ] );
}

uint16_t HardwareReader::getSpeed()
{
    return analogRead( potentioPIN );
}
