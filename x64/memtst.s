format ELF64

public memtst_back
memtst_back:
	mov	rax, rbp
bt_up:	cmp	rdi, 0
	jle	bt_out
	test	rax, rax
	jz	bt_out
	mov	rax, [rax]
	dec	rdi
	jmp	bt_up
bt_out:	test	rax, rax
	jz	bt_ret
	add	rax, 8
	mov	rax, [rax]
bt_ret:	ret
