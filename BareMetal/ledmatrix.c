#include "ledmatrix.h"

void picture_init()
{
    for (uint32_t row = 0; row < 8; ++row)
    {
        for (uint32_t col = 0; col < 8; ++col)
        {
            picture[row][col].b = 1 << row;
            picture[row][col].g = 1 << (7 - row);
            picture[row][col].r = 1 << col;
        }
    }
}

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

    // Wait 100 ms
    // 80 MHz ~ 4E7 loops /s
    // 100 ms ~ 4E6 loops

    for (uint32_t i = 0; i < 5 * 1000 * 1000; ++i)
    {
        asm("nop");
    }

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

    picture_init();
}

void RST(pinValue x)
{
    GPIOC->BSRR |= (x == HIGH ? GPIO_BSRR_BS3 : GPIO_BSRR_BR3); 
}

void SB(pinValue x)
{
    GPIOC->BSRR |= (x == HIGH ? GPIO_BSRR_BS5 : GPIO_BSRR_BR5); 
}

void LAT(pinValue x)
{
    GPIOC->BSRR |= (x == HIGH ? GPIO_BSRR_BS4 : GPIO_BSRR_BR4); 
}

void SCK(pinValue x)
{
    GPIOB->BSRR |= (x == HIGH ? GPIO_BSRR_BS1 : GPIO_BSRR_BR1); 
}

void SDA(pinValue x)
{
    GPIOA->BSRR |= (x == HIGH ? GPIO_BSRR_BS4 : GPIO_BSRR_BR4); 
}

void ROW(uint32_t addr, pinValue x)
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
void SCK_pulse()
{
    SCK(LOW);
    SCK(HIGH);
    SCK(LOW);
}


void LAT_pulse()
{
    LAT(HIGH);
    // At least 25ns here
    asm("nop");
    asm("nop");
    LAT(LOW);
    LAT(HIGH);
}

void deactivate_rows(){
    for (uint32_t i = 0; i < 8; ++i)
    {
        ROW(i, LOW);
    }
}

void send_byte(uint8_t val, int bank)
{
    SB(bank ? HIGH : LOW);

    for (uint32_t i = 0; i < 8; ++i)
    {
        SDA((val & (1 << (7 - i))) >> (7 - i));
        SCK_pulse();
    }
}

void set_row(uint8_t row, const rgb_color* value)
{
    for (uint32_t i = 0; i < 8; ++i)
    {
        send_byte(value[i].b, 1);
        send_byte(value[i].g, 1);
        send_byte(value[i].r, 1);
    }

    LAT_pulse();

    ROW((row + 7) % 8, LOW);

    ROW(row, HIGH);
}

void show_picture()
{
    for (uint32_t row = 0; row < 8; ++row)
    {
        set_row(row, picture[row]);
    }
}

void test_matrix()
{
    show_picture();
}