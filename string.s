format ELF

public memcpy
memcpy:
	push	esi
	push	edi
	mov	edi, [esp+12]
	mov	esi, [esp+16]
	mov	ecx, [esp+20]
	mov	eax, edi
	cld
	rep movsb
	pop	edi
	pop	esi
	ret

public memmove
memmove:
	push	esi
	push	edi
	mov	edi, [esp+12]
	mov	esi, [esp+16]
	mov	ecx, [esp+20]
	cmp	edi, esi
	jng	.usual
	mov	eax, esi
	add	eax, ecx
	cmp	edi, eax
	jg	.usual

	mov	eax, edi
	std
	add	esi, ecx
	add	edi, ecx
	dec	esi
	dec	edi
	rep movsb
	jmp	.ret
.usual:
	mov	eax, edi
	cld
	rep movsb
.ret:
	pop	edi
	pop	esi
	ret

public memset
memset:
	push	edi
	mov	edi, [esp+8]
	mov	eax, [esp+12]
	mov	ecx, [esp+16]
	mov	edx, edi
	cld
	rep stosb
	pop	edi
	mov	eax, edx
	ret

public memchr
memchr:
	mov	eax, [esp+8]
	mov	ecx, [esp+12]
	push	edi
	mov	edi, [esp+8]
	cld
	repnz scasb
	jne	.failed
	mov	eax, edi
	dec	eax
	jmp	.ret
.failed:
	xor	eax, eax
.ret:
	pop	edi
	ret

public memcmp
memcmp:
	push	esi
	push	edi
	xor	eax, eax
	mov	esi, [esp+12]
	mov	edi, [esp+16]
	mov	ecx, [esp+20]
	jecxz	.ret

	cld
	rep cmpsb
	jz	.ret
	sbb	eax, eax
	or	eax, 1
.ret:
	pop 	edi
	pop 	esi
	ret

public strlen
strlen:
	push	edi
	mov	edi, [esp+8]
	xor	eax, eax
	mov	ecx, -1
	cld
	repnz scasb
	mov	eax, ecx
	not	eax
	dec	eax
	pop	edi
	ret

public memrchr
memrchr:
	mov	eax, [esp+8]
	mov	ecx, [esp+12]
	push	edi
	mov	edi, [esp+8]
	add	edi, ecx
	dec	edi
	std
	repnz scasb
	jne	.failed
	mov	eax, edi
	inc	eax
	jmp	.ret
.failed:
	xor	eax, eax
.ret:
	pop	edi
	ret

public strchr
strchr:
	mov	ecx, [esp+4]
	mov	edx, [esp+8]
.loop:
	mov	al, [ecx]
	cmp	al, dl
	jz	.done
	inc	ecx
	test	al, al
	jnz	.loop
	xor	ecx, ecx
.done:
	mov	eax, ecx
	ret

public strcmp
strcmp:
	mov	ecx, [esp+4]
	mov	edx, [esp+8]
	xor	eax, eax
.loop:
	mov	al, [ecx]
	cmp	al, [edx]
	jnz	.ret
	inc	edx
	inc	ecx
	test	al, al
	jnz	.loop
	ret
.ret:
	movzx	ecx, byte [edx]
	sub	eax, ecx
	ret

public strcpy
strcpy:
	push	edi
	push	esi
	mov	edx, [esp+12]
	mov	esi, [esp+16]
	mov	edi, edx
	cld
.loop:
	lodsb
	stosb
	or	al, al
	jnz	.loop
	pop	esi
	pop	edi
	mov	eax, edx
	ret

public strrchr
strrchr:
	push	edi
	mov	edi, [esp+8]
	mov	ecx, [esp+12]
	xor	edx, edx
	dec	edi
.loop:
	inc	edi
	test	al, al
	jz	.done
	mov	al, [edi]
	cmp	al, cl
	jnz	.loop
	mov	edx, edi
	jz	.loop
.done:
	mov	eax, edx
	pop	edi
	ret
