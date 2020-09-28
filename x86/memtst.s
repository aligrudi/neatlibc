


global memtst_back
memtst_back:
	mov	eax, ebp
	mov	ecx, [esp+4]
bt_up:	cmp	ecx, 0
	jle	bt_out
	test	eax, eax
	jz	bt_out
	mov	eax, [eax]
	dec	ecx
	jmp	bt_up
bt_out:	test	eax, eax
	jz	bt_ret
	mov	eax, [eax+4]
bt_ret:	ret
