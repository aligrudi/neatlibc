format ELF64

public htonl
public ntohl
htonl:
ntohl:
	mov	eax, edi
	xchg	al, ah
	ror	eax, 16
	xchg	al, ah
	ret

public htons
public ntohs
htons:
ntohs:
	mov	eax, edi
	ror	ax, 8
	ret
