#define STM32L475xx
#include "stm32l4xx.h"
#include <stdint.h>
#include "clocks.h"
#include "ledmatrix.h"
#include "irq.h"
#include "buttons.h"

int main()
{
    irq_init();
    button_init();
    clocks_init();
    matrix_init();

    uint32_t row = 0;

    while(1)
    {
        test_matrix();
    }

    return 0;
}