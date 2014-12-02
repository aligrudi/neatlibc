format ELF

public __memcpylong
__memcpylong:
	push	esi
	push	edi
	mov	edi, [esp+12]
	mov	esi, [esp+16]
	mov	ecx, [esp+20]
	mov	eax, edi
	shr	ecx, 2
	cld
	rep movsd
	pop	edi
	pop	esi
	ret

public __memsetlong
__memsetlong:
	push	edi
	mov	edi, [esp+8]
	mov	eax, [esp+12]
	mov	ecx, [esp+16]
	mov	edx, edi
	shr	ecx, 2
	cld
	rep stosd
	pop	edi
	mov	eax, edx
	ret
