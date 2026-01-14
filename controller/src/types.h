#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef int State;
#define WIFI_CONNECTED 1

typedef struct {
    float x;
    float y;
    bool buttonPressed;
} joystick_data ;


#endif