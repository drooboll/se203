.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
	ldr r0, =0x10008000
	mov sp, r0

    ldr r0, =0xdeadbeef
    ldr r1, =0x10000100
    mov r2, #256
    bl mem_fill

	ldr r0, =0x10000100
	mov r1, #256
	ldr r2, =0x10000300
	bl mem_cpy
	
	
stop:
	b stop

/*
Pattern     	r0
Dst addr        r1
Dst len         r2
*/
mem_fill:
    mov r3, #0
_mem_fill_loop:
    str r0, [r1, r3]
    add r3, r3, #4
    cmp r3, r2
    bne _mem_fill_loop

    bx lr

/*
Source addr		r0
Src length		r1
Dst addr		r2
Ret: fin addr	r0
*/
mem_cpy:
	push {r4, r5}
	mov r4, #0	@ Counter
_mem_cpy_loop:
	ldrb r5, [r0, r4]
	strb r5, [r2, r4]
	add r4, #1
	cmp r4, r1
	bne _mem_cpy_loop

	add r0, r2, r4
	add r0, r0, #1
	pop {r4, r5}
	bx lr
