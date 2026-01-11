#ifndef COMM_H
#define COMM_H

#include "types.h"

void send_data(joystick_data *data);
char* create_json_string(joystick_data *data);
char* create_http_post_string(const char* json_string);

#endif