#include "hardware/pio.h"
#include "pico/stdlib.h"

#include "pulse.pio.h"

int main()
{
    const uint led_pin = PICO_DEFAULT_LED_PIN;
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    const uint pulse_pin = 2;

    PIO pio = pio0;
    uint offset = pio_add_program(pio, &pulse_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pulse_program_init(pio, sm, offset, pulse_pin);

    while (true)
    {
        gpio_put(led_pin, true);
        sleep_ms(250);
        gpio_put(led_pin, false);
        sleep_ms(250);
    }
}
