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

BaseType_t get_joystick_data(joystick_data *data) {
    return xQueuePeek(joystick_queue, data, 0);
}

State get_state() { return xEventGroupGetBits(system_events); }
void set_state(State state) { xEventGroupSetBits(system_events, state); }
