#include <stdio.h>
#include <string.h>

#include <pico/stdlib.h>

#include <FreeRTOS.h>
#include <task.h>

#include "joystick_task.h"

int main() {
    stdio_init_all();
    sleep_ms(300);

    if(!create_joystick_task()) {
        printf("Joystick Task creation failed\n");
        return 0;
    }

    vTaskStartScheduler();

    return 0;
}