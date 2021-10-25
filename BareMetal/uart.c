#include "uart.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

volatile uint8_t uartBuffer[3 * 8 * 8];
volatile size_t bufferPosition = 0;

void uart_init(uint32_t baudrate)
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
	// Both Tx & Rx + input match + rx interrupts
	USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_CMIE | USART_CR1_RXNEIE;
	// Define input match on 0xff
	USART1->CR2 |= 0xff << USART_CR2_ADD_Pos;

	USART1->BRR = F_CPU / baudrate;

	// Enable UART
	USART1->CR1 |= 1 << USART_CR1_UE_Pos;

	NVIC_EnableIRQ(USART1_IRQn);
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

void uart_sum(size_t count)
{
	uint32_t sum = 0;

	for (size_t i = 0; i < count; ++i)
	{
		sum += uart_getchar();
	}

	char buf[10];

	itoa(buf, sum);

	uart_puts(buf);
	uart_puts("\r\n");
}

void USART1_IRQHandler()
{
	uint32_t isr = USART1->ISR;

	if (isr & USART_ISR_CMF)
	{
		bufferPosition = 0;

		bufferFullFlag = 0;

		USART1->ICR |= USART_ICR_CMCF;

		uint32_t dummy = USART1->RDR;

		return;
	}

	if (isr & USART_ISR_RXNE)
	{
		uartBuffer[bufferPosition++] = (uint8_t) USART1->RDR;

		if (bufferPosition == 8 * 8 * 3)
		{
			bufferFullFlag = 1;

			// Avoid bad things
			bufferPosition = 0;
		}

		return;
	}

	// Debug
	while (1)
	{
		asm("nop");
	}
}

uint32_t uart_buffer_full()
{
	return bufferFullFlag;
}

uint32_t uart_buffer_full_reset()
{
	bufferFullFlag = 0;
}