#include "wifi.h"
#include "system_state.h"
#include "config.h"
#include <pico/cyw43_arch.h>
#include <lwip/sockets.h>
#include <cyw43_ll.h>

bool connect_to_wifi() {
    if (cyw43_arch_init()) {
        unset_state(WIFI_CONNECTED);
        return false;
    }

    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        unset_state(WIFI_CONNECTED);
        return false;
    }

    set_state(WIFI_CONNECTED);
    return true;
}

void send_data_over_wifi(const char* data) {
    int socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr.s_addr = inet_addr(SERVER_IP)
    };

    int result = connect(socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (result == 0) {
        send(socket, data, strlen(data), 0);
    }

    closesocket(socket);
}

bool is_wifi_connected() {
    State state = get_state();
    return (state & WIFI_CONNECTED) != 0;
}
