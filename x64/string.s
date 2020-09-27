


global memcpy
memcpy:
	mov	rax, rdi
	mov	rcx, rdx
	cld
	rep movsb
	ret

global memmove
memmove:
	mov	rcx, rdx
	cmp	rdi, rsi
	jng	.usual
	mov	rax, rsi
	add	rax, rcx
	cmp	rdi, rax
	jg	.usual

	mov	rax, rdi
	std
	add	rsi, rcx
	add	rdi, rcx
	dec	rsi
	dec	rdi
	rep movsb
	ret
.usual:
	mov	rax, rdi
	cld
	rep movsb
	ret

global memset
memset:
	mov	rcx, rdx
	mov	rax, rsi
	mov	rdx, rdi
	cld
	rep stosb
	mov	rax, rdx
	ret

global memchr
memchr:
	mov	rax, rsi
	mov	rcx, rdx
	test	rcx, rcx
	jz	.failed
	cld
	repnz scasb
	jne	.failed
	mov	rax, rdi
	dec	rax
	ret
.failed:
	xor	eax, eax
	ret

global memcmp
memcmp:
	xor	eax, eax
	mov	rcx, rdx
	jecxz	.ret

	cld
	rep cmpsb
	jz	.ret
	xor	eax, eax
	mov	al, [rdi - 1]
	xor	ecx, ecx
	mov	cl, [rsi - 1]
	sub	eax, ecx
.ret:
	ret

global strlen
strlen:
	xor	eax, eax
	mov	rcx, -1
	cld
	repnz scasb
	mov	rax, rcx
	not	rax
	dec	rax
	ret

global memrchr
memrchr:
	mov	eax, esi
	mov	rcx, rdx
	add	rdi, rcx
	dec	rdi
	test	rcx, rcx
	jz	.failed
	std
	repnz scasb
	jne	.failed
	mov	rax, rdi
	inc	rax
	ret
.failed:
	xor	eax, eax
	ret

global strchr
strchr:
.loop:
	mov	al, [rdi]
	cmp	al, sil
	jz	.done
	inc	rdi
	test	al, al
	jnz	.loop
	xor	edi, edi
.done:
	mov	rax, rdi
	ret

global strcmp
strcmp:
	xor	eax, eax
.loop:
	mov	al, [rdi]
	cmp	al, [rsi]
	jnz	.ret
	inc	rdi
	inc	rsi
	test	al, al
	jnz	.loop
	ret
.ret:
	movzx	rcx, byte [rsi]
	sub	rax, rcx
	ret

global strcpy
strcpy:
	mov	rdx, rdi
	cld
.loop:
	lodsb
	stosb
	or	al, al
	jnz	.loop
	mov	rax, rdx
	ret

global strrchr
strrchr:
	xor	edx, edx
	dec	rdi
.loop:
	inc	rdi
	mov	al, [rdi]
	test	al, al
	jz	.done
	cmp	al, sil
	jnz	.loop
	mov	rdx, rdi
	jmp	.loop
.done:
	mov	rax, rdx
	ret

global strncmp
strncmp:
	xor	eax, eax
.loop:
	test	rdx, rdx
	jz	.failed
	mov	al, [rdi]
	cmp	al, [rsi]
	jnz	.ret
	inc	rsi
	inc	rdi
	dec	rdx
	test	al, al
	jnz	.loop
.failed:
	xor	eax, eax
	ret
.ret:
	movzx	ecx, byte [rsi]
	sub	eax, ecx
	ret
