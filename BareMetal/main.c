#include <stdint.h>
#include "gpio.h"

uint8_t i = 0;

void stupidDelay()
{
    // Guess that at 8Mhz that's ~250 ms
    for (uint32_t i = 0; i < 500000; ++i)
    {
        asm("nop");
    }
}

int main()
{
    gpio_init(GPIOB, 14);
    gpio_init(GPIOC, 9);

    while(1)
    {
        gpio_set(GPIOC, 9, ON);
        stupidDelay();
        gpio_set(GPIOC, 9, OFF);
        gpio_init(GPIOB, 14);
        gpio_set(GPIOB, 14, ON);
        stupidDelay();
        gpio_set(GPIOB, 14, OFF);
        stupidDelay();
        gpio_deinit(GPIOB, 14);
    }

    return 0;
}