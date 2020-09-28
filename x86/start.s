


extern environ

extern main
extern __neatlibc_exit
global _start
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
	call	__neatlibc_exit
	mov	eax, 0x1
	int	0x80
