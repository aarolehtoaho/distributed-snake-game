#include <pico/stdlib.h>
#include <hardware/adc.h>

#include "joystick.h"
#include "config.h"

void init_joystick() {
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);

    gpio_init(JOYSTICK_BTN_PIN);
    gpio_set_dir(JOYSTICK_BTN_PIN, GPIO_IN);
    gpio_pull_up(JOYSTICK_BTN_PIN);
}

bool button_pressed() {
    return gpio_get(JOYSTICK_BTN_PIN) == 0;
}

float read_joystick_x() {
    adc_select_input(JOYSTICK_X_PIN - 26);
    uint16_t raw = adc_read();
    return raw / 4095.0f;
}

float read_joystick_y() {
    adc_select_input(JOYSTICK_Y_PIN - 26);
    uint16_t raw = adc_read();
    return raw / 4095.0f;
}
