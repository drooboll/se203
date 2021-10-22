#ifndef BUTTONS_H
#define BUTTONS_H

#include "irq.h"

void button_init();
void EXTI15_10_IRQHandler();

#endif