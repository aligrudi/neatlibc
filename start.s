format ELF

extrn main
public _start
_start:
	xor	ebp, ebp
	pop	ecx
	mov	edx, esp
	push	edx
	push	ecx
	call	main
	mov	ebx, eax
	mov	eax, 0x1
	int	0x80
