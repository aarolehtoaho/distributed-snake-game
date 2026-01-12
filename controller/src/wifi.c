#include <stdio.h>

#include "wifi.h"
#include "system_state.h"
#include "config.h"
#include <pico/cyw43_arch.h>
#include <lwip/api.h>
#include <cyw43_ll.h>

bool wifi_init() {
    printf("Print 1\n");
    if (cyw43_arch_init()) { // cyw43_arch_init() freezes
        printf("init failed\n");
        return false;
    }
    printf("Print 2\n");
    cyw43_arch_enable_sta_mode();
    return true;
}

bool wifi_connect() {
    printf("Connecting to WiFi...\n");
    fflush(stdout);
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Failed to connect to WiFi\n");
        fflush(stdout);
        unset_state(WIFI_CONNECTED);
        return false;
    }
    printf("Connected to WiFi successfully\n");
    fflush(stdout);
    set_state(WIFI_CONNECTED);
    return true;
}

void send_data_over_wifi(const char* data) {
    struct netconn *conn;
    ip_addr_t server_ip;

    ipaddr_aton(SERVER_IP, &server_ip);

    conn = netconn_new(NETCONN_TCP);
    if (!conn) return;

    if (netconn_connect(conn, &server_ip, SERVER_PORT) == ERR_OK) {
        netconn_write(conn, data, strlen(data), NETCONN_COPY);
    }

    netconn_close(conn);
    netconn_delete(conn);
}

bool is_wifi_connected() {
    State state = get_state();
    return (state & WIFI_CONNECTED) != 0;
}
