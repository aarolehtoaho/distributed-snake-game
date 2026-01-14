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
        printf("Sending HTTP POST\n");
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
    int json_len = strlen(json_string);
    int buffer_size = 300 + json_len;
    
    char *http_string = (char *)malloc(buffer_size);
    if (!http_string) {
        printf("ERROR: Failed to allocate memory for HTTP string\n");
        return NULL;
    }
    
    int written = snprintf(http_string, buffer_size,
            "POST /data HTTP/1.1\r\n"
            "Host: %s:%d\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: %d\r\n"
            "Connection: close\r\n"
            "\r\n"
            "%s",
            SERVER_IP,
            SERVER_PORT,
            json_len,
            json_string);
    
    if (written < 0 || written >= buffer_size) {
        printf("ERROR: HTTP string formatting failed\n");
        free(http_string);
        return NULL;
    }
    
    return http_string;
}