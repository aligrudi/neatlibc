


global __memcpylong
__memcpylong:
	mov	rax, rdi
	mov	rcx, rdx
	shr	ecx, 3
	cld
	rep movsq
	ret

global __memsetlong
__memsetlong:
	mov	rcx, rdx
	mov	rax, rsi
	mov	rdx, rdi
	shr	ecx, 3
	cld
	rep stosq
	mov	rax, rdx
	ret
