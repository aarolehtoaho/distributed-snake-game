#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include <FreeRTOS.h>
#include <queue.h>
#include <event_groups.h>

#include "types.h"

extern QueueHandle_t joystick_queue;
extern EventGroupHandle_t system_events;

void init_system_state();
void write_joystick_data(joystick_data *data);
BaseType_t get_joystick_data(joystick_data *data);
State get_state();
void unset_state(State state);
void set_state(State state);

#endif