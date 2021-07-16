#include "pico/stdlib.h"

int main()
{
    const uint led_pin = PICO_DEFAULT_LED_PIN;
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    gpio_put(led_pin, false);

    const uint pulse_pin = 2;
    gpio_init(pulse_pin);
    gpio_set_dir(pulse_pin, GPIO_OUT);

    gpio_put(led_pin, true);

    while (true)
    {
        gpio_put(pulse_pin, true);
        sleep_ms(1);
        gpio_put(pulse_pin, false);
        sleep_ms(1);
    }
}
