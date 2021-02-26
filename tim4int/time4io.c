#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw( void ){
    int value = PORTD;
    return (value >> 8) & 0x000F;
    //'0'000
}

int getbtns( void ){
    int value = PORTD;
    return (value >> 5) & 0x0007;
}