format ELF

public memcpy
public memmove
memcpy:
memmove:
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
	pop	edi
	pop	esi
	mov	eax, edx
	ret
