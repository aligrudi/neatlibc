.extern environ
.extern main
.extern __neatlibc_exit

.global _start
_start:
	mov	fp, #0
	ldr	r0, [sp], #4		@ argc
	mov	r1, sp			@ argv
	add	r2, r1, r0, lsl #2
	add	r2, r2, #4		@ envp
	ldr	r12, =environ
	str	a3, [r12]

	bl	main
	mov	r4, r0
	bl	__neatlibc_exit
	mov	r0, r4

	mov	r7, #1
	swi	#0
