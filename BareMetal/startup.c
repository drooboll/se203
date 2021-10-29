#include <stdint.h>

extern uint8_t __bss_start, __bss_end, __text_lma, __data_lma, __text, __etext, __data, __edata;
extern uint8_t __irq_handlers_lma, __irq_handlers, __eirq_handlers;

void __attribute__ ((section (".xip"))) __init_bss()
{
    uint8_t* current = &__bss_start;
    while(current < &__bss_end)
    {
        *(current++) = 0;
    }
}

void __attribute__ ((section (".xip"))) __copy_text()
{
    uint8_t* dst = &__text;
    uint8_t* src = &__text_lma;
    while (dst < &__etext)
        *dst++ = *src++;
}

void __attribute__ ((section (".xip"))) __copy_data()
{
    uint8_t* dst = &__data;
    uint8_t* src = &__data_lma;
    while (dst < &__edata)
        *dst++ = *src++;
}

void __attribute__ ((section (".xip"))) __move_irq_handlers()
{
    uint8_t* dst = &__irq_handlers;
    uint8_t* src = &__irq_handlers_lma;
    while (dst < &__eirq_handlers)
        *dst++ = *src++;
}