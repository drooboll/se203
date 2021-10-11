#define STM32L475xx
#define F_CPU 80000000UL
#include "stm32l4xx.h"
#include <stdint.h>
#include <memory.h>

// This is very stupid library without interrupts (yet?)
void uart_init();
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
void uart_puts(const char *s);
void uart_gets(char *s, size_t size);
void uart_gets_separator(char *s, size_t size, char sep);
