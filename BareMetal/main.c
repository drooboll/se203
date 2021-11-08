#define STM32L475xx
#include "stm32l4xx.h"
#include <stdint.h>
#include "clocks.h"
#include "ledmatrix.h"
#include "irq.h"
#include "buttons.h"
#include "uart.h"
#include "timer.h"

volatile uint32_t step = 0;

void callback_specific()
{
    show_picture();

    if(step == 100)
    {
        life_step();
        step = 0;
    }

    step++;
}

int main()
{
    clocks_init();
    matrix_init();
    irq_init();
    button_init();
    timer_init(1);
    timer_set_callback(callback_specific);

    uart_init(38400);
    uart_set_callback(update_picture);

    start_life();

    while(1)
    {  
    }

    return 0;
}