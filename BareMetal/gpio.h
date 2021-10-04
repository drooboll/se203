#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

#include <stdint.h>
static uint32_t * const RCC_BaseAddress = (uint32_t*) 0x40021000;
static const uint32_t AHB2_offset = 0x4C >> 2;
static uint32_t * const GPIOA_BaseAddress = (uint32_t*) 0x48000000;
static const uint32_t GPIO_Set_size = 0x400 >> 2;
static const uint32_t MODER_offset = 0x00 >> 2;
static const uint32_t OTYPER_offset = 0x04 >> 2;
static const uint32_t OSPEEDR_offset = 0x08 >> 2;
static const uint32_t PUPDR_offset = 0x0C >> 2;
static const uint32_t IDR_offset = 0x10 >> 2;
static const uint32_t ODR_offset = 0x14 >> 2;
static const uint32_t BSSR_offset = 0x18 >> 2;

typedef enum
{
    GPIOA = 0,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH,
    GPIOI
} GPIO_TypeDef;

typedef enum
{
    OFF = 0,
    ON,
    HIZ
} GPIO_Value;

void gpio_init(GPIO_TypeDef gpio, uint32_t gpio_num);
void gpio_deinit(GPIO_TypeDef gpio, uint32_t gpio_num);
void gpio_set(GPIO_TypeDef gpio, uint32_t gpio_num, GPIO_Value value);

#endif