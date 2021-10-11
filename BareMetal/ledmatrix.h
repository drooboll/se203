#ifndef CLOCKS_H
#define CLOCKS_H

#define STM32L475xx
#include "stm32l4xx.h"
#include <stdint.h>

typedef enum
{
    LOW = 0,
    HIGH
} pinValue;

void RST(pinValue x);
void SB(pinValue x);
void LAT(pinValue x);
void SCK(pinValue x);
void SDA(pinValue x);
void ROW(uint32_t addr, pinValue x);

void SCK_pulse();
void LAT_pulse();
void deactivate_rows();

void send_byte(uint8_t val, int bank);

void set_row(uint8_t row, const rgb_color* value);

void matrix_init();

typedef struct
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
} rgb_color;

#endif