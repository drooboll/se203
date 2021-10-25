#define STM32L475xx
#include "stm32l4xx.h"
#include <stdint.h>
#include "clocks.h"
#include "ledmatrix.h"
#include "irq.h"
#include "buttons.h"
#include "uart.h"

int main()
{
    irq_init();
    button_init();
    clocks_init();
    matrix_init();
    uart_init(38400);

    while(1)
    {  
        if (uart_buffer_full())
        {
            update_picture(uartBuffer);

            uart_buffer_full_reset();
        }

        show_picture();
    }

    return 0;
}