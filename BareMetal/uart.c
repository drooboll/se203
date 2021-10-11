#include "uart.h"

void uart_init()
{
	// Enable GPIO
	RCC->AHB2ENR |= 1 << RCC_AHB2ENR_GPIOBEN_Pos;
	RCC->APB2ENR |= 1 << RCC_APB2ENR_USART1EN_Pos;
	// USART1 TX PB6 AF7
	// USART1 RX PB7 AF7
	GPIOB->MODER &= ~(GPIO_MODER_MODE6 | GPIO_MODER_MODE7);
	GPIOB->MODER |= 0b10 << GPIO_MODER_MODE6_Pos | 0b10 << GPIO_MODER_MODE7_Pos;
	GPIOB->AFR[0] |= 0b0111 << GPIO_AFRL_AFSEL7_Pos | 0b0111 << GPIO_AFRL_AFSEL6_Pos;

	// PCLK
	RCC->CCIPR &= RCC_CCIPR_USART1SEL_Msk;
	// Both Tx & Rx
	USART1->CR1 |= 1 << USART_CR1_RE_Pos | 1 << USART_CR1_TE_Pos;

	// Baud 115200 (maybe) OVER8 = 0 by default
	USART1->BRR = F_CPU / 115200;

	// Enable UART
	USART1->CR1 |= 1 << USART_CR1_UE_Pos;
}

void uart_putchar(uint8_t c)
{
	while (!(USART1->ISR & USART_ISR_TXE))
	{
		asm("nop");
	}

	USART1->TDR = c;
}

uint8_t uart_getchar()
{
	while(!(USART1->ISR & USART_ISR_RXNE))
	{
		asm("nop");
	}

	uint8_t data = USART1->RDR;

	return data;
}

void uart_puts(const char *s)
{
	// Hope you are using null-terminated strings, right?
	while (*s != 0)
	{
		uart_putchar(*(s++));
	}
}

// size_t? Really?
void uart_gets(char *s, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		*(s + i) = uart_getchar();
	}

	s[size] = 0;
}

// Maximum length of size
// Or until separator symbol
// SENDS BACK EVERY SYMBOL
void uart_gets_separator(char *s, size_t size, char sep)
{
	for (size_t i = 0; i < size; ++i)
	{
		*(s + i) = uart_getchar();
		uart_putchar(*(s + i));

		if (*(s + i) == sep)
		{
			*(s + i + 1) = 0;
			break;
		}
	}
}