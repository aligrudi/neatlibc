format ELF

public htonl
public ntohl
htonl:
ntohl:
	mov	eax, [esp+4]
	xchg	al, ah
	ror	eax, 16
	xchg	al, ah
	ret

public htons
public ntohs
htons:
ntohs:
	mov	eax, [esp+4]
	ror	ax, 8
	ret
