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
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
    GPIOD->MODER &= ~(0b11 << GPIO_MODER_MODE5_Pos | 0b11 << GPIO_MODER_MODE4_Pos);
    GPIOD->MODER |= (0b01 << GPIO_MODER_MODE5_Pos | 0b01 << GPIO_MODER_MODE4_Pos);
    GPIOD->OSPEEDR |= (0b11 << GPIO_OSPEEDR_OSPEED5_Pos | 0b11 << GPIO_OSPEEDR_OSPEED4_Pos);

    clocks_init();
    matrix_init();
    irq_init();
    button_init();
    timer_init(10);
    timer_set_callback(show_picture);

    uart_init(38400);
    uart_set_callback(update_picture);

    while(1)
    {  
    }

    return 0;
}