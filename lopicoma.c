#include <stdio.h>

#include "hardware/pio.h"
#include "pico/stdlib.h"

#include "fifo.pio.h"

int main()
{
    // 108MHz clock (13.5 * 8)
    set_sys_clock_khz(108 * 1000, true);

    // Must happen after clocks are configured
    stdio_init_all();

    printf("Clocks and stdio initialized correctly\n");

    const uint led_pin = PICO_DEFAULT_LED_PIN;
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_put(led_pin, true);

    const uint dac_base_pin = 2;

    PIO pio = pio0;
    uint offset = pio_add_program(pio, &fifo_program);
    uint sm = pio_claim_unused_sm(pio, true);
    fifo_program_init(pio, sm, offset, dac_base_pin);

    while (true)
    {
        uint32_t packed = (0 << 24) | (64 << 16) | (128 << 8) | (192 << 0);
        pio_sm_put_blocking(pio, sm, packed);
        /*for (uint i = 0; i < 256; i += 4)
        {
            uint32_t packed = 0;
            for (uint j = 0; j < 4; j++)
                packed = (packed << 8) | (i + j);
            pio_sm_put_blocking(pio, sm, packed);
        }*/
    }
}
