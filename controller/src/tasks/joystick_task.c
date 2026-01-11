#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>

#include "config.h"
#include "joystick_task.h"
#include "joystick.h"

static void joystick_task(void *arg) {
    (void)arg;

    init_joystick();

    for(;;){
        if (button_pressed()) {
            printf("Button is pressed\n");
        }
        printf("Joystick X: %f\n", read_joystick_x());
        printf("Joystick Y: %f\n", read_joystick_y());
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(JOYSTICK_TASK_PERIOD_MS + 300));
    }
}

bool create_joystick_task() {
    TaskHandle_t joystickTaskHandle = NULL;
    BaseType_t result = xTaskCreate(joystick_task, "joystick", DEFAULT_STACK_SIZE, NULL, 2, &joystickTaskHandle);
    return result == pdPASS ? true : false;
}