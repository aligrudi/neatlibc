


global htonl
global ntohl
htonl:
ntohl:
	mov	eax, edi
	xchg	al, ah
	ror	eax, 16
	xchg	al, ah
	ret

global htons
global ntohs
htons:
ntohs:
	mov	eax, edi
	ror	ax, 8
	ret
