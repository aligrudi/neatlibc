#include <string.h>

#define LONG01	(0x01010101ul | (0x01010101ul << (sizeof(long) * 8 - 32)))
#define LONG80	(0x80808080ul | (0x80808080ul << (sizeof(long) * 8 - 32)))
#define LONGOFF(s)	((unsigned long) s & (sizeof(long) - 1))
#define HASZERO(x)	(((x) - LONG01) & ~(x) & LONG80)

void *__memchr_c(void *src, int c, long n)
{
	unsigned char *s = src;
	c = (unsigned char) c;
	unsigned long k = LONG01 * c;
	while (LONGOFF(s) && n && *s != c)
		s++, n--;
	if (n && *s != c) {
		unsigned long *w = (void *) s;
		while (n >= sizeof(long) && !HASZERO(*w ^ k))
			w++, n -= sizeof(long);
		s = (void *) w;
	}
	while (n && *s != c)
		s++, n--;
	return n ? (void *) s : 0;
}
