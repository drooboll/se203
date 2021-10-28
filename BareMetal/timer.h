#ifndef _TIMERS_H
#define _TIMERS_H

#define STM32L475xx
#include "stm32l4xx.h"
#include <stddef.h>
#include <stdint.h>

#define F_CPU 80000000UL

static void (*timer_callback)(void) = NULL;

void timer_init(uint32_t ms);

void timer_set_callback(void (*c)(void));

#endif