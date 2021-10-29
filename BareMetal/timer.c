#include "timer.h"

void timer_init(uint32_t ms)
{
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    TIM2->SR = 0;
    TIM2->CNT = 0;
    TIM2->PSC = ms;
    TIM2->ARR = F_CPU / ms / 250;
    TIM2->DIER |= TIM_DIER_UIE;
    
    NVIC_EnableIRQ(TIM2_IRQn);
    // Set priority of 45 -- Higher than USART
    NVIC_SetPriority(TIM2_IRQn, 45);

    TIM2->CR1 |= TIM_CR1_CEN;
}

void timer_set_callback(void (*c)(void))
{
    timer_callback = c;
}

void TIM2_IRQHandler()
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        if (timer_callback != NULL)
        {
            timer_callback();
        }

        TIM2->SR &= ~(TIM_SR_UIF);
    }
}