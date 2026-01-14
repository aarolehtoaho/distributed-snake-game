#include <stdio.h>

#include "wifi.h"
#include "system_state.h"
#include "config.h"
#include <pico/cyw43_arch.h>
#include <lwip/api.h>
#include <lwip/netif.h>
#include <cyw43_ll.h>

bool wifi_init() {
    if (cyw43_arch_init()) {
        printf("init failed\n");
        return false;
    }
    printf("cyw43_arch_init succeeded\n");
    cyw43_arch_enable_sta_mode();
    return true;
}

bool wifi_connect() {
    printf("Connecting to WiFi...\n");
    fflush(stdout);
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 20000)) {
        printf("Failed to connect to WiFi\n");
        fflush(stdout);
        unset_state(WIFI_CONNECTED);
        return false;
    }
    printf("Connected to WiFi successfully\n");
    printf("IP: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_default)));
    fflush(stdout);
    set_state(WIFI_CONNECTED);
    return true;
}

void send_data_over_wifi(const char* data) {
    struct netconn *conn;
    ip_addr_t server_ip;

    ipaddr_aton(SERVER_IP, &server_ip);

    conn = netconn_new(NETCONN_TCP);
    if (!conn) {
        printf("ERROR: Failed to create new netconn\n");
        return;
    }

    err_t err = netconn_connect(conn, &server_ip, SERVER_PORT); // Not connecting
    if (err == ERR_OK) {
        // Turn led on to indicate data is being sent
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        printf("Data sent to %s:%d\n", SERVER_IP, SERVER_PORT);
        netconn_write(conn, data, strlen(data), NETCONN_COPY);
    } else {
        // Turn led off to indicate failure
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        printf("ERROR: Failed to connect to server %s:%d, Error: %d\n", SERVER_IP, SERVER_PORT, err);
    }

    netconn_close(conn);
    netconn_delete(conn);
}

bool is_wifi_connected() {
    State state = get_state();
    return (state & WIFI_CONNECTED) != 0;
}
