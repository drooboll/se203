ENTRY(main)
MEMORY
{
    SRAM1 (rwx) : org = 0x20000000, LENGTH = 96K
    SRAM2 (rwx) : org = 0x10000000, LENGTH = 32K
    Flash (rx) : org = 0x08000000, LENGTH = 1M
}

SECTIONS
{
    .text : 
    {
        *(.text)
    } > SRAM1
    .rodata :
    {
        *(.rodata)
    }
    .data :
    {
        *(.data)
    } > SRAM1
    .bss :
    {
        *(.bss) *(COMMON)
    } > SRAM1
}
