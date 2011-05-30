format ELF

extrn environ

extrn main
public _start
_start:
	xor	ebp, ebp
	pop	ecx
	mov	edx, esp
	push	ecx

	lea	eax, [edx + ecx * 4 + 4]
	mov	[environ], eax

	push	eax
	push	edx
	push	ecx
	call	main
	mov	ebx, eax
	mov	eax, 0x1
	int	0x80
