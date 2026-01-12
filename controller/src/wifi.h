#ifndef WIFI_H
#define WIFI_H

#include <stdbool.h>

bool wifi_init();
bool wifi_connect();
void send_data_over_wifi(const char* data);
bool is_wifi_connected();

#endif