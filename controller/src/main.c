#include <stdio.h>
#include <string.h>

#include <pico/stdlib.h>

#include <FreeRTOS.h>
#include <task.h>

#include "joystick_task.h"
#include "comm_task.h"
#include "system_state.h"

int main() {
    stdio_init_all();
    sleep_ms(300);
    
    init_system_state();

    if(!create_joystick_task()) {
        printf("Joystick Task creation failed\n");
        return 0;
    }

    if (!create_comm_task()) {
        printf("Communication Task creation failed\n");
        return 0;
    }

    vTaskStartScheduler();

    return 0;
}