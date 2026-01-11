#ifndef WIFI_H
#define WIFI_H

#include <stdbool.h>

bool connect_to_wifi();
void send_data_over_wifi(const char* data);
bool is_wifi_connected();

#endif