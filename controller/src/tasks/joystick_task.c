#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

#include "types.h"
#include "config.h"
#include "joystick_task.h"
#include "joystick.h"
#include "system_state.h"

static void joystick_task(void *arg) {
    (void)arg;

    init_joystick();
    joystick_data data;

    for(;;) {
        data.buttonPressed = button_pressed();
        data.x = read_joystick_x();
        data.y = read_joystick_y();
        write_joystick_data(&data);

        vTaskDelay(pdMS_TO_TICKS(JOYSTICK_TASK_PERIOD_MS));
    }
}

bool create_joystick_task() {
    TaskHandle_t joystickTaskHandle = NULL;
    BaseType_t result = xTaskCreate(joystick_task, "joystick", DEFAULT_STACK_SIZE, NULL, 2, &joystickTaskHandle);
    return result == pdPASS ? true : false;
}