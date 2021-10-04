#define STM32L475xx
#include <stdint.h>
#include "clocks.h"
#include "stm32l4xx.h"

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
    clocks_init();

    RCC->AHB2ENR |= 1 << RCC_AHB2ENR_GPIOBEN_Pos;
    GPIOB->MODER &= ~(0b11 << GPIO_MODER_MODE14_Pos);
    GPIOB->MODER |= 0b01 << GPIO_MODER_MODE14_Pos;

    RCC->AHB2ENR |= 1 << RCC_AHB2ENR_GPIOCEN_Pos;
    GPIOC->MODER &= ~(0b11 << GPIO_MODER_MODE9_Pos);
    GPIOC->MODER |= 0b01 << GPIO_MODER_MODE9_Pos;

    while(1)
    {
        GPIOC->BSRR |= 1 << GPIO_BSRR_BR9_Pos; // Disable Green
        GPIOB->MODER |= 0b01 << GPIO_MODER_MODE14_Pos;
        GPIOB->BSRR |= 1 << GPIO_BSRR_BS14_Pos; // Yellow
        stupidDelay();
        GPIOB->BSRR |= 1 << GPIO_BSRR_BR14_Pos; // Blue
        stupidDelay();
        GPIOB->MODER &= ~(0b11 << GPIO_MODER_MODE14_Pos); // Disable YB
        GPIOC->BSRR |= 1 << GPIO_BSRR_BS9_Pos; // Green
        stupidDelay();
    }

    return 0;
}