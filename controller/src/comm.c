#include <cJSON.h>
#include <stdlib.h>
#include <pico/time.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "comm.h"
#include "wifi.h"

void send_data(joystick_data *data) {
    if (is_wifi_connected()) {
        char *json_string = create_json_string(data);
        char *http_post_string = create_http_post_string(json_string);
        send_data_over_wifi(http_post_string);
        free(http_post_string);
        free(json_string);
    }
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

char* create_http_post_string(const char* json_string) {
    char *http_string;
    sprintf(http_string,
            "POST /data HTTP/1.1\r\n"
            "Host: %s\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: %d\r\n"
            "\r\n"
            "%s",
            SERVER_IP,
            strlen(json_string),
            json_string);
    return http_string;
}