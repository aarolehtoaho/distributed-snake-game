#include <stdio.h>
#include <stdint.h>
#include "system_state.h"

QueueHandle_t joystick_queue = NULL;
EventGroupHandle_t system_events = NULL;

void init_system_state() {
    joystick_queue = xQueueCreate(1, sizeof(joystick_data));
    if (joystick_queue == NULL) {
        printf("ERROR: Failed to create joystick queue\n");
        return;
    }
    
    system_events = xEventGroupCreate();
    if (system_events == NULL) {
        printf("ERROR: Failed to create event group\n");
        return;
    }
    
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
