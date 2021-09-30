.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
	ldr r0, =0x10001000
	mov sp, r0
	
	mov r0, test_string
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

	push {r4, r5, r6, lr}
	mov r4, #0
	push {r0-r3}

	mov r0, r3
	b idiv
	mov r5, r0 @ Number of repetitions
	pop {r0-r3}
	mov r6, r0 @ Preserve start address

_mem_fill_loop:
	bl mem_cpy
	mov r2, r0 @ Update dst address
	mov r0, r6 @ Return srs address to r0
	add r4, #1
	cmp r4, r5
	bne _mem_fill_loop

	pop {r4, r5, r6, lr}
	bx lr


_mem_fill_error:
	mov r0, #0
	bx lr

/*
String address	r0
Ret: string len	r0
 */
strcmp:
	mov r1, #0
	mov r2, r1
_strcmp_loop:
	ldrb r3, [r0, r1]
	add r1, r1, #1
	cmp r3, r2
	bne _strcmp_loop

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
	add r2, #0
	cmp r0, r1
	ble _idiv_loop

	mov r1, r0
	mov r0, r2
	bx lr

.section .rodata
addr_pattern: .word 0xdeadbeef
test_string: .asciz "Test string!"
