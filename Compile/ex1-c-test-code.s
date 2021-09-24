	.cpu arm7tdmi
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 4
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"ex1-c-test-code.c"
	.text
	.align	2
	.global	f
	.arch armv4t
	.syntax unified
	.arm
	.fpu softvfp
	.type	f, %function
f:
	@ Function supports interworking.
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r4, #0
	ldr	r5, .L4
.L2:
	bl	g
	add	r4, r4, #1
	ldr	r3, [r5]
	and	r4, r4, #255
	cmp	r4, r3
	bls	.L2
.L5:
	.align	2
.L4:
	.word	a
	.size	f, .-f
	.comm	a,4,4
	.ident	"GCC: (15:9-2019-q4-0ubuntu1) 9.2.1 20191025 (release) [ARM/arm-9-branch revision 277599]"
