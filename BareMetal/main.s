	.cpu arm7tdmi
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.global	i
	.bss
	.type	i, %object
	.size	i, 1
i:
	.space	1
	.text
	.align	1
	.global	main
	.arch armv4t
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
.L4:
	ldr	r3, .L5
	ldrb	r3, [r3]
	cmp	r3, #99
	bhi	.L2
	ldr	r3, .L5
	ldrb	r3, [r3]
	adds	r3, r3, #1
	lsls	r3, r3, #24
	lsrs	r2, r3, #24
	ldr	r3, .L5
	strb	r2, [r3]
	b	.L4
.L2:
	ldr	r3, .L5
	movs	r2, #0
	strb	r2, [r3]
	b	.L4
.L6:
	.align	2
.L5:
	.word	i
	.size	main, .-main
	.ident	"GCC: (15:9-2019-q4-0ubuntu1) 9.2.1 20191025 (release) [ARM/arm-9-branch revision 277599]"
