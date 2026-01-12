#include <stdio.h>
#include "system_task.h"
#include "wifi.h"
#include "config.h"
#include "types.h"
#include "system_state.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

static void system_task(void *arg) {
    (void)arg;

    for(;;) {
        if (!is_wifi_connected()) {
            wifi_connect();
        }
        vTaskDelay(pdMS_TO_TICKS(SYSTEM_TASK_PERIOD_MS));
    }
}

bool create_system_task() {
    TaskHandle_t systemTaskHandle = NULL;
    BaseType_t result = xTaskCreate(system_task, "system", DEFAULT_STACK_SIZE, NULL, 2, &systemTaskHandle);
    return result == pdPASS ? true : false;
}