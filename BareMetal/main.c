#define STM32L475xx
#include "stm32l4xx.h"
#include <stdint.h>
#include "clocks.h"
#include "ledmatrix.h"
#include "irq.h"
#include "buttons.h"
#include "uart.h"
#include "timer.h"

int main()
{
    clocks_init();
    matrix_init();
    irq_init();
    button_init();
    timer_init(1);
    timer_set_callback(show_picture);

    uart_init(38400);
    uart_set_callback(update_picture);

    while(1)
    {  
    }

    return 0;
}