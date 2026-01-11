#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef enum { WIFI_CONNECTED } State ;
typedef struct {
    float x;
    float y;
    bool buttonPressed;
} joystick_data ;


#endif