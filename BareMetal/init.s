    .cpu arm7tdmi
    .syntax unified
    .global _start
    .thumb
    .section .xip, "ax"
    .thumb_func
_start:
    @ init SP
    ldr r0, =__sp_start
    mov sp, r0
    @ call bss init
    bl __init_bss
    @ copy text & data
    bl __copy_text
    bl __copy_data
    bl __move_irq_handlers
    @ call main
    ldr r0, _exit
    mov lr, r0
    ldr r0, =main
    mov pc, r0
    @ something wrong
_exit:
    b _exit
