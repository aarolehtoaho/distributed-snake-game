#include <cJSON.h>
#include <stdlib.h>
#include <pico/time.h>
#include "comm.h"

void send_data(joystick_data *data) {
    char *json_string = create_json_string(data);

    // TODO: Send JSON string using wifi

    free(json_string);
}

char* create_json_string(joystick_data *data) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "device_id", "pico-joystick-01");
    cJSON_AddNumberToObject(root, "x", data->x);
    cJSON_AddNumberToObject(root, "y", data->y);
    cJSON_AddBoolToObject(root, "button", data->buttonPressed);
    cJSON_AddNumberToObject(root, "timestamp", to_ms_since_boot(get_absolute_time()));

    char *json_string = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);

    return json_string;
}