
.global memcpy
memcpy:
	mov	r12, r0
.loop:
	subs	r2, r2, #1
	bmi	.ret
	ldrb	r3, [r1], #1
	strb	r3, [r0], #1
	b	.loop
.ret:
	mov	r0, r12
	mov	pc, lr

.global memset
memset:
	mov	r12, r0
.loop:
	subs	r2, r2, #1
	bmi	.ret
	strb	r1, [r0], #1
	b	.loop
.ret:
	mov	r0, r12
	mov	pc, lr

.global memmove
memmove:
	mov	r12, r0
	cmp	r0, r1
	ble	.fw
	add	r3, r1, r2
	cmp	r0, r3
	bgt	.fw

	@ copying the memory in reverse order
	add	r0, r0, r2
	add	r1, r1, r2
.bw:
	subs	r2, r2, #1
	bmi	.ret
	ldrb	r3, [r1, #-1]!
	strb	r3, [r0, #-1]!
	b	.bw
.fw:
	subs	r2, r2, #1
	bmi	.ret
	ldrb	r3, [r1], #1
	strb	r3, [r0], #1
	b	.fw
.ret:
	mov	r0, r12
	mov	pc, lr

.global memchr
memchr:
	subs	r2, r2, #1
	bmi	.failed
	ldrb	r3, [r0], #1
	cmp	r3, r1
	bne	memchr
	b	.ret
.failed:
	mov	r0, #0
.ret:
	mov	pc, lr

.global memcmp
memcmp:
	subs	r2, r2, #1
	bmi	.match
	ldrb	r3, [r0], #1
	ldrb	r12, [r1], #1
	subs	r3, r3, r12
	movne	r0, r3
	bne	.ret
	b	memcmp
.match:
	mov	r0, #0
.ret:
	mov	pc, lr

.global strlen
strlen:
	mov	r2, r0
.loop:
	ldrb	r1, [r0], #1
	tst	r1, r1
	bne	.loop
	sub	r0, r0, r2
	sub	r0, r0, #1
	mov	pc, lr

.global strchr
strchr:
	ldrb	r2, [r0], #1
	cmp	r1, r2
	subeq	r0, r0, #1
	beq	.ret
	tst	r2, r2
	bne	strchr
	mov	r0, #0
.ret:
	mov	pc, lr

.global strcmp
strcmp:
	ldrb	r2, [r0], #1
	ldrb	r3, [r1], #1
	cmp	r2, #1
	cmpcs	r2, r3
	beq	strcmp
	sub	r0, r2, r3
	mov	pc, lr

.global strcpy
strcpy:
	mov	r3, r0
.loop:
	ldrb	r2, [r1], #1
	strb	r2, [r0], #1
	tst	r2, r2
	bne	.loop
	mov	r0, r3
.ret:
	mov	pc, lr
