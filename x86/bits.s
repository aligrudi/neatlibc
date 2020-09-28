


global htonl
global ntohl
htonl:
ntohl:
	mov	eax, [esp+4]
	xchg	al, ah
	ror	eax, 16
	xchg	al, ah
	ret

global htons
global ntohs
htons:
ntohs:
	mov	eax, [esp+4]
	ror	ax, 8
	ret
