#include "gpio.h"

void gpio_init(GPIO_TypeDef gpio, uint32_t gpio_num)
{
	*(RCC_BaseAddress + AHB2_offset) |= 1 << gpio;
	// Output
	*(GPIOA_BaseAddress + GPIO_Set_size * gpio + MODER_offset) &= ~(0b11 << (gpio_num << 1));
	*(GPIOA_BaseAddress + GPIO_Set_size * gpio + MODER_offset) |= 0b01 << (gpio_num << 1);
}

void gpio_deinit(GPIO_TypeDef gpio, uint32_t gpio_num)
{
	gpio_set(gpio, gpio_num, OFF);

	*(GPIOA_BaseAddress + GPIO_Set_size * gpio + MODER_offset) |= 0b11 << (gpio_num << 1);
}

void gpio_set(GPIO_TypeDef gpio, uint32_t gpio_num, GPIO_Value value)
{
	if (value)
		*(GPIOA_BaseAddress + GPIO_Set_size * gpio + BSSR_offset) |= 1 << gpio_num;
	else
		*(GPIOA_BaseAddress + GPIO_Set_size * gpio + BSSR_offset) |= (1 << gpio_num) << 16;
}