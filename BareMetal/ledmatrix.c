#include "ledmatrix.h"
#include <memory.h>

void matrix_init()
{
    RCC->AHB2ENR |=  RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN;

    // All as outputs
    // PA4, PA15, PA2, PA7, PA6, PA5, PA3
    GPIOA->MODER &= ~(0b11 << GPIO_MODER_MODE4_Pos | 0b11 << GPIO_MODER_MODE15_Pos | 0b11 << GPIO_MODER_MODE2_Pos |
                      0b11 << GPIO_MODER_MODE7_Pos | 0b11 << GPIO_MODER_MODE6_Pos | 0b11 << GPIO_MODER_MODE5_Pos |
                      0b11 << GPIO_MODER_MODE3_Pos);
    GPIOA->MODER |= 0b01 << GPIO_MODER_MODE4_Pos | 0b01 << GPIO_MODER_MODE15_Pos | 0b01 << GPIO_MODER_MODE2_Pos |
                    0b01 << GPIO_MODER_MODE7_Pos | 0b01 << GPIO_MODER_MODE6_Pos | 0b01 << GPIO_MODER_MODE5_Pos |
                    0b01 << GPIO_MODER_MODE3_Pos;

    GPIOA->OSPEEDR |= 0b11 << GPIO_OSPEEDR_OSPEED4_Pos | 0b11 << GPIO_OSPEEDR_OSPEED15_Pos |
                      0b11 << GPIO_OSPEEDR_OSPEED2_Pos | 0b11 << GPIO_OSPEEDR_OSPEED7_Pos |
                      0b11 << GPIO_OSPEEDR_OSPEED6_Pos | 0b11 << GPIO_OSPEEDR_OSPEED5_Pos |
                      0b11 << GPIO_OSPEEDR_OSPEED3_Pos;

    // All as outputs
    // PB1, PB2, PB0
    GPIOB->MODER &= ~(0b11 << GPIO_MODER_MODE0_Pos | 0b11 << GPIO_MODER_MODE1_Pos | 0b11 << GPIO_MODER_MODE2_Pos);
    GPIOB->MODER |= 0b01 << GPIO_MODER_MODE0_Pos | 0b01 << GPIO_MODER_MODE1_Pos | 0b01 << GPIO_MODER_MODE2_Pos;

    GPIOB->OSPEEDR |= 0b11 << GPIO_OSPEEDR_OSPEED0_Pos | 0b11 << GPIO_OSPEEDR_OSPEED1_Pos |
                      0b11 << GPIO_OSPEEDR_OSPEED2_Pos;
    // All as outputs
    // PC5, PC4, PC3
    GPIOC->MODER &= ~(0b11 << GPIO_MODER_MODE5_Pos | 0b11 << GPIO_MODER_MODE4_Pos | 0b11 << GPIO_MODER_MODE3_Pos);
    GPIOC->MODER |= 0b01 << GPIO_MODER_MODE5_Pos | 0b01 << GPIO_MODER_MODE4_Pos | 0b01 << GPIO_MODER_MODE3_Pos;

    GPIOC->OSPEEDR |= 0b11 << GPIO_OSPEEDR_OSPEED3_Pos | 0b11 << GPIO_OSPEEDR_OSPEED4_Pos |
                      0b11 << GPIO_OSPEEDR_OSPEED5_Pos;

    RST(HIGH);

    RST(LOW);
    LAT(HIGH);
    SB(HIGH);
    SCK(LOW);
    SDA(LOW);

    deactivate_rows();

    // Wait 100 ms
    // 80 MHz ~ 4E7 loops /s
    // 100 ms ~ 4E6 loops

    for (uint32_t i = 0; i < 5 * 1000 * 1000; ++i)
    {
        asm("nop");
    }

    // Should be reset already
    RST(HIGH);

    // Set BANK0
    for (uint8_t i = 0; i < 6; ++i)
    {
        send_byte(0xff, 0);
    }

    LAT_pulse();

    // Set default picture
    memcpy((void*) imageBuffer, (void*) &_binary_image_raw_start, sizeof(imageBuffer));
}

static inline void RST(pinValue x)
{
    GPIOC->BSRR |= (x == HIGH ? GPIO_BSRR_BS3 : GPIO_BSRR_BR3); 
}

static inline void SB(pinValue x)
{
    GPIOC->BSRR |= (x == HIGH ? GPIO_BSRR_BS5 : GPIO_BSRR_BR5); 
}

static inline void LAT(pinValue x)
{
    GPIOC->BSRR |= (x == HIGH ? GPIO_BSRR_BS4 : GPIO_BSRR_BR4);
    GPIOD->BSRR |= (x == HIGH ? GPIO_BSRR_BS5 : GPIO_BSRR_BR5); 
}

static inline void SCK(pinValue x)
{
    GPIOB->BSRR |= (x == HIGH ? GPIO_BSRR_BS1 : GPIO_BSRR_BR1);
    GPIOD->BSRR |= (x == HIGH ? GPIO_BSRR_BS3 : GPIO_BSRR_BR3); 
}

static inline void SDA(pinValue x)
{
    GPIOA->BSRR |= (x > LOW ? GPIO_BSRR_BS4 : GPIO_BSRR_BR4);
    GPIOD->BSRR |= (x > LOW ? GPIO_BSRR_BS4 : GPIO_BSRR_BR4); 
}

static inline void ROW(uint32_t addr, pinValue x)
{
    switch (addr)
    {
    case 0:
        GPIOB->BSRR |= (x == HIGH ? GPIO_BSRR_BS2 : GPIO_BSRR_BR2);
        break;
    case 1:
        GPIOA->BSRR |= (x == HIGH ? GPIO_BSRR_BS15 : GPIO_BSRR_BR15);
        break;
    case 2:
        GPIOA->BSRR |= (x == HIGH ? GPIO_BSRR_BS2 : GPIO_BSRR_BR2);
        break;
    case 3:
        GPIOA->BSRR |= (x == HIGH ? GPIO_BSRR_BS7 : GPIO_BSRR_BR7);
        break;
    case 4:
        GPIOA->BSRR |= (x == HIGH ? GPIO_BSRR_BS6 : GPIO_BSRR_BR6);
        break;
    case 5:
        GPIOA->BSRR |= (x == HIGH ? GPIO_BSRR_BS5 : GPIO_BSRR_BR5);
        break;
    case 6:
        GPIOB->BSRR |= (x == HIGH ? GPIO_BSRR_BS0 : GPIO_BSRR_BR0);
        break;
    case 7:
        GPIOA->BSRR |= (x == HIGH ? GPIO_BSRR_BS3 : GPIO_BSRR_BR3);
        break;
    default:
        break;
    }
}

// 2ms minimum for clock pulse
// Each closk is 1/8E7 = 12.5 ns
// No need for delay 
static void SCK_pulse()
{
    SCK(LOW);
    SCK(HIGH);
    SCK(LOW);
}


static void LAT_pulse()
{
    LAT(HIGH);
    asm("nop");
    asm("nop");
    LAT(LOW);
    asm("nop");
    asm("nop");
    LAT(HIGH);
}

static void deactivate_rows(){
    for (uint32_t i = 0; i < 8; ++i)
    {
        ROW(i, LOW);
    }
}

static void send_byte(uint8_t val, int bank)
{
    SB(bank ? HIGH : LOW);

    for (uint32_t i = 0; i < 8; ++i)
    {
        SDA(val & (1 << (7 - i)));
        SCK_pulse();
    }
}

static inline void set_row(uint8_t row, const rgb_color* value)
{
    for (uint32_t i = 0; i < 8; ++i)
    {
        send_byte(value[7-i].b, 1);
        send_byte(value[7-i].g, 1);
        send_byte(value[7-i].r, 1);
    }

    deactivate_rows();

    // M54564 deactivate time up to 5us (avoid interleaving)
    for (volatile uint32_t i = 0; i < 100; ++i)
    {
        asm("nop");
    }

    LAT_pulse(); 
    
    ROW(row, HIGH);
}

static volatile uint8_t currentRow = 0;

void show_picture()
{
    deactivate_rows();

    set_row(currentRow, imageBuffer + currentRow * 8);

    currentRow++;

    currentRow %= 8;
}



void update_picture(uint8_t* newPicture)
{
    memcpy((void*) imageBuffer, (void*) newPicture, sizeof(imageBuffer));
}

void start_life()
{
    memset(imageBuffer, 0, 192);

    imageBuffer[1].g = 254;
    imageBuffer[8 + 2].g = 254;
    imageBuffer[16].g = 254;
    imageBuffer[16 + 1].g = 254;
    imageBuffer[16 + 2].g = 254;
}

uint32_t test_color(uint8_t i, uint8_t j)
{
    return imageBuffer[i + j * 8].b << 16 | imageBuffer[i + j * 8].g << 8 | imageBuffer[i + j * 8].r;
}

void life_step()
{
    rgb_color localBuffer[64] = {(0)};

    memcpy(localBuffer, imageBuffer, sizeof(imageBuffer));

    for (uint8_t i = 0; i < 8; ++i)
    {
        for (uint8_t j = 0; j < 8; ++j)
        {
            uint32_t topLeft = test_color((i + 7) % 8, (j + 7) % 8) == 0 ? 0 : 1;
            uint32_t left = test_color((i + 7) % 8, j) == 0 ? 0 : 1;
            uint32_t bottomLeft = test_color((i + 7) % 8, (j + 1) % 8) == 0 ? 0 : 1;

            uint32_t top = test_color(i, (j + 7) % 8) == 0 ? 0 : 1;
            uint32_t bottom = test_color(i, (j + 1) % 8) == 0 ? 0 : 1;

            uint32_t topRight = test_color((i + 1) % 8, (j + 7) % 8) == 0 ? 0 : 1;
            uint32_t right = test_color((i + 1) % 8, j) == 0 ? 0 : 1;
            uint32_t bottomRight = test_color((i + 1) % 8, (j + 1) % 8) == 0 ? 0 : 1;

            uint32_t num = topLeft + left + bottomLeft + top + bottom + topRight + right + bottomRight;
                
            if (test_color(i, j))
            {
                if (num > 3 || num < 2)
                {
                    localBuffer[i + j * 8].g = 0; 
                }
            }
            else
            {
                if (num == 3)
                {
                    localBuffer[i + j * 8].g = 254; 
                }
            }
        }
    }

    memcpy(imageBuffer, localBuffer, sizeof(localBuffer));
}