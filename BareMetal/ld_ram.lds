ENTRY(_start);
__sp_start = ORIGIN(SRAM2) + LENGTH(SRAM2);
__flash_start = ORIGIN(FLASH);
__text_lma = LOADADDR(.text);
__data_lma = LOADADDR(.data);
__irq_handlers_lma = LOADADDR(.irq_handlers);

MEMORY
{
    SRAM1 (rwx) : org = 0x20000000, LENGTH = 96K
    SRAM2 (rwx) : org = 0x10000000, LENGTH = 32K
    FLASH (rx) : org = 0x08000000, LENGTH = 1M
}

SECTIONS
{
    .irq_handlers : ALIGN(256)
    {
        __irq_handlers = .;
        *(.irq_handlers)
        __eirq_handlers = .;
    } >SRAM1 AT>FLASH
    .xip :
    {
        *(.xip)   
    } > FLASH
    .text : 
    {
        __text = .;
        *(.text)
        __etext = .;
    } >SRAM1 AT>FLASH
    .data :
    {
        __data = .;
        *(.data)
        __edata = .;
    } >SRAM1 AT>FLASH
    .rodata :
    {
        *(.rodata)
    } >FLASH
    .bss :
    {
        __bss_start = .;
        *(.bss) *(COMMON)
        __bss_end = .;
    } >SRAM1
}
