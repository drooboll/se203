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

    uart_puts("Checksum>\r\n");

    while(1)
    {
        uart_sum(1000);
    }

    return 0;
}