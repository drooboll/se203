/*

uint32_t a; // global variable...

for (uint8_t i=0; i<=a; i++)
    g();

 */
.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
@ Call f...

f:
    ldr r0, a
    ldr r1, [r0]


g:
    bx lr

a: .word #0x00000042