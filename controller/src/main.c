#include <stdio.h>
#include <string.h>

#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <boards/pico.h>

#include "joystick_task.h"
#include "comm_task.h"
#include "system_task.h"
#include "system_state.h"
#include "wifi.h"

int main() {
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    sleep_ms(1000);
    
    init_system_state();

    if(!create_joystick_task()) {
        printf("Joystick Task creation failed\n");
        return 0;
    }

    if (!create_comm_task()) {
        printf("Communication Task creation failed\n");
        return 0;
    }

    if (!create_system_task()) {
        printf("System Task creation failed\n");
        return 0;
    }

    vTaskStartScheduler();

    return 0;
}