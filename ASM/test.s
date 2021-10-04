.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
	ldr r0, =0x10008000
	mov sp, r0
	
	ldr r0, adr_string
	bl strlen

	mov r1, r0
	add r1, #1 @ Copy zero
	ldr r0, adr_string
	ldr r2, =0x10000400
	mov r3, #4
	mul r3, r1, r3
	bl mem_fill
stop:
	b stop
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

/*
Source addr		r0
Src length		r1
Dst addr		r2
Dst length		r3
ret: success	r0
 */
mem_fill:
	cmp r1, r3
	bhi _mem_fill_error

	push {r4-r8, lr}
	mov r4, r0 @ src a
	mov r5, r1 @ src len
	mov r6, r2 @ dst a

	mov r0, r3
	bl idiv
	mov r7, r0 @ Repeat count
	mov r8, #0 @ Counter

_mem_fill_loop:
	mov r0, r4
	mov r1, r5
	mov r2, r6

	bl mem_cpy
	add r6, r6, r5 @ inc dst addr 
	add r8, #1
	cmp r8, r7
	bne _mem_fill_loop

	pop {r4-r8, lr}
	bx lr


_mem_fill_error:
	mov r0, #0
	bx lr

/*
String address	r0
Ret: string len	r0
 */
strlen:
	mov r1, #0
	mov r2, r1
_strcmp_loop:
	ldrb r3, [r0, r1]
	add r1, r1, #1
	cmp r3, r2
	bne _strcmp_loop

	sub r1, #1 @ Because of do-while
	mov r0, r1
	bx lr

/*
Dividee			r0
Divider			r1
ret: quitent	r0
ret: reminder	r1
 */
idiv:
	mov r2, #0
_idiv_loop:
	sub r0, r1
	add r2, #1
	cmp r0, r1
	bge _idiv_loop

	mov r1, r0
	mov r0, r2
	bx lr

adr_string: .word test_string

.section .data
addr_pattern: .word 0xdeadbeef
test_string: .asciz "Test string!"
