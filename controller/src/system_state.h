#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include <FreeRTOS.h>
#include <queue.h>
#include <event_groups.h>

#include "types.h"

extern QueueHandle_t joystick_data_queue;
extern EventGroupHandle_t system_events;

void init_system_state();
void write_joystick_data(joystick_data *data);
State getState();
void setState(State state);

#endif