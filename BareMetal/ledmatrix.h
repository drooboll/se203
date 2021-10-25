#ifndef MATRIX_H
#define MATRIX_H

#define STM32L475xx
#include "stm32l4xx.h"
#include <stdint.h>

typedef enum
{
    LOW = 0,
    HIGH
} pinValue;

typedef struct matrix_color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color;

extern rgb_color _binary_image_raw_start, _binary_image_raw_end; 

rgb_color imageBuffer[8 * 8];

static void RST(pinValue x);
static void SB(pinValue x);
static void LAT(pinValue x);
static void SCK(pinValue x);
static void SDA(pinValue x);
static void ROW(uint32_t addr, pinValue x);

static void SCK_pulse();
static void LAT_pulse();
static void deactivate_rows();

static void send_byte(uint8_t val, int bank);

static void set_row(uint8_t row, const rgb_color* value);

void matrix_init();

void show_picture();

void update_picture();

#endif