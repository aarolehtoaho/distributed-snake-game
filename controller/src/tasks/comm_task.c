#include <stdio.h>

#include "comm_task.h"
#include "comm.h"
#include "types.h"
#include "config.h"
#include "system_state.h"

static void comm_task(void *arg) {
    (void)arg;

    joystick_data data;

    for(;;) {
        if (get_joystick_data(&data) == pdTRUE) {
            send_data(&data);
        }

        vTaskDelay(pdMS_TO_TICKS(JOYSTICK_TASK_PERIOD_MS));
    }
}

bool create_comm_task() {
    TaskHandle_t commTaskHandle = NULL;
    BaseType_t result = xTaskCreate(comm_task, "comm", DEFAULT_STACK_SIZE, NULL, 2, &commTaskHandle);
    return result == pdPASS ? true : false;
}