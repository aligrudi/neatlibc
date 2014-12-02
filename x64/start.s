format ELF64

extrn environ

extrn main
extrn __neatlibc_exit
public _start
_start:
	xor	rbp, rbp
	pop	rdi			; argc
	mov	rsi, rsp		; argv
	push	rdi
	lea	rdx, [rsi + rdi * 8 + 8]; envp
	mov	[environ], rdx
	and	rsp, -16		; align rsp

	call	main
	mov	rbx, rax
	call	__neatlibc_exit
	mov	rdi, rbx
	mov	rax, 60
	syscall
