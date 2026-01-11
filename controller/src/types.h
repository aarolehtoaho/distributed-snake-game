#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

typedef enum { READ, SEND } State ;
typedef struct {
    float x;
    float y;
    bool buttonPressed;
} joystick_data ;


#endif