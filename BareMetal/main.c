#define STM32L475xx
#include "stm32l4xx.h"
#include <stdint.h>
#include "clocks.h"
#include "uart.h"

uint8_t i = 0;

int main()
{
    clocks_init();
    uart_init();

    uart_puts("Testing test>\r\n");

    while(1)
    {
        uint8_t rec = uart_getchar();
        uart_putchar(rec);
    }

    return 0;
}