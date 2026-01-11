#ifndef JOYSTICK_H
#define JOYSTICK_H

void init_joystick();
bool button_pressed();
float read_joystick_x();
float read_joystick_y();

#endif