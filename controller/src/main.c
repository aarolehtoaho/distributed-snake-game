#include <stdio.h>
#include <string.h>

#include <pico/stdlib.h>

#include <FreeRTOS.h>
#include <task.h>

#define DEFAULT_STACK_SIZE 2048 

enum state { IDLE=1 };
enum state programState = IDLE;

static void example_task(void *arg){
    (void)arg;

    for(;;){
        printf("Example print");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

int main() {
    stdio_init_all();
    sleep_ms(300);

    TaskHandle_t myExampleTask = NULL;
    // Create the tasks with xTaskCreate
    BaseType_t result = xTaskCreate(example_task, "example", DEFAULT_STACK_SIZE, NULL, 2, &myExampleTask);

    if(result != pdPASS) {
        printf("Example Task creation failed\n");
        return 0;
    }

    vTaskStartScheduler();

    return 0;
}