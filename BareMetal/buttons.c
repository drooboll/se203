#include "buttons.h"

void button_init()
{
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    // Enable also a led port
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOBEN;

    // Input mode
    GPIOC->MODER &= ~(0b11 << GPIO_MODER_MODE13_Pos);
    // Output mode
    GPIOB->MODER &= ~(0b11 << GPIO_MODER_MODE14_Pos);
    GPIOB->MODER |= 0b01 << GPIO_MODER_MODE14_Pos;

    uint32_t regvalue = SYSCFG->EXTICR[3];

    // EXTI13 as PC13
    regvalue &= ~(0b1111 << SYSCFG_EXTICR4_EXTI13_Pos);
    regvalue |= 0b0010 << SYSCFG_EXTICR4_EXTI13_Pos;

    SYSCFG->EXTICR[3] = regvalue;

    // Unmask interrupt
    EXTI->IMR1 |= EXTI_IMR1_IM13;
    // Use only falling edge
    EXTI->FTSR1 |= EXTI_FTSR1_FT13;
    
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler()
{
    uint32_t value = EXTI->PR1;

    if (value & EXTI_PR1_PIF13)
    {
        GPIOB->BSRR |= 1 << ((GPIOB->ODR & GPIO_ODR_OD14) ? GPIO_BSRR_BR14_Pos : GPIO_BSRR_BS14_Pos);
    }

    EXTI->PR1 |= value;
}