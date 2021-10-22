#ifndef IRQ_H
#define IRQ_H

#define STM32L475xx
#include "stm32l4xx.h"

#include <stdint.h>
#include <memory.h>

#define MAKE_DEFAULT_HANDLER(x) void __attribute__((weak)) x(void)\
{\
    __disable_irq();\
    while(1)\
    {\
        asm("nop");\
    }\
}

extern uint32_t __sp_start, _start;

void irq_init();

#endif