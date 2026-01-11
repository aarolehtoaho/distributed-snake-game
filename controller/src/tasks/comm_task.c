#include <stdio.h>

#include "comm_task.h"
#include "types.h"
#include "config.h"
#include "system_state.h"

static void comm_task(void *arg) {
    (void)arg;

    joystick_data data;

    for(;;) {
        set_state(SEND);

        get_joystick_data(&data);
        printf("(%f, %f), button: %d\n", data.x, data.y, data.buttonPressed);

        vTaskDelay(pdMS_TO_TICKS(JOYSTICK_TASK_PERIOD_MS + 500));
    }
}

bool create_comm_task() {
    TaskHandle_t commTaskHandle = NULL;
    BaseType_t result = xTaskCreate(comm_task, "comm", DEFAULT_STACK_SIZE, NULL, 2, &commTaskHandle);
    return result == pdPASS ? true : false;
}