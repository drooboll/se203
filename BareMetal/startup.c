#include <stdint.h>

extern uint8_t __bss_start, __bss_end;

void __init_bss()
{
    uint8_t* current = &__bss_start;
    while(current < &__bss_end)
    {
        *(current++) = 0;
    }
}