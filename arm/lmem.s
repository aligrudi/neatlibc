
.global __memcpylong
__memcpylong:
	mov	r12, r0
.loop:	subs	r2, r2, #4
	bmi	.ret
	ldr	r3, [r1], #4
	str	r3, [r0], #4
	b	.loop
.ret:	mov	r0, r12
	mov	pc, lr

.global __memsetlong
__memsetlong:
	mov	r12, r0
.loop:	subs	r2, r2, #4
	bmi	.ret
	str	r1, [r0], #4
	b	.loop
.ret:	mov	r0, r12
	mov	pc, lr
