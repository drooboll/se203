    .cpu arm7tdmi
    .syntax unified
    .global _start
    .thumb
_start:
    @ init SP
    ldr r0, =__sp_start
    mov sp, r0
    @ call bss init
    bl __init_bss
    @ call main
    bl main
    @ something wrong
_exit:
    b _exit
