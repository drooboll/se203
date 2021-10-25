#ifndef UART_H
#define UART_H

#define STM32L475xx
#define F_CPU 80000000UL
#include "stm32l4xx.h"
#include <stdint.h>
#include <memory.h>

extern volatile uint8_t uartBuffer[3 * 8 * 8];
extern volatile size_t bufferPosition;

static volatile uint32_t bufferFullFlag = 0;

// This is (less stupid) library with interrupts
void uart_init(uint32_t baudrate);
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
void uart_puts(const char *s);
void uart_gets(char *s, size_t size);
void uart_gets_separator(char *s, size_t size, char sep);
void uart_sum(size_t count);
uint32_t uart_buffer_full();
uint32_t uart_buffer_full_reset();

#endif
