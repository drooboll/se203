    .cpu arm7tdmi
    .syntax unified
    .global _start
    .thumb
_start:
    @ init SP
    ldr r0, =0x10007000
    mov sp, r0
    @ call bss init
    bl __init_bss
    @ call main
    bl main
    @ something wrong
_exit:
    b _exit
