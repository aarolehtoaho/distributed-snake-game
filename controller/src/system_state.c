#include <stdint.h>
#include "system_state.h"

QueueHandle_t joystick_queue = NULL;
EventGroupHandle_t system_events = NULL;

void init_system_state() {
    joystick_queue = xQueueCreate(1, sizeof(joystick_data));
    system_events = xEventGroupCreate();
    xEventGroupSetBits(system_events, READ);
}

void write_joystick_data(joystick_data *data) {
    xQueueOverwrite(joystick_queue, data);
}

State getState() { return xEventGroupGetBits(system_events); }
void setState(State state) { xEventGroupSetBits(system_events, state); }
