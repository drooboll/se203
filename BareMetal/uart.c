#include "uart.h"

void uart_init()
{
	RCC->APB2ENR |= 1 << RCC_APB2ENR_USART1EN_Pos;
	// Both Tx & Rx
	USART1->CR1 |= 1 << USART_CR1_RE_Pos | 1 << USART_CR1_TE_Pos;

	// Baud 9600 (maybe) OVER8 = 0 by default
	USART1->BRR = 2 * F_CPU / 9600;

	// Enable UART
	USART1->CR1 |= 1 << USART_CR1_UE_Pos;
}

void uart_putchar(uint8_t c)
{

}

uint8_t uart_getchar()
{

}

void uart_puts(const char *s)
{

}

// size_t? Really?
void uart_gets(char *s, size_t size)
{

}