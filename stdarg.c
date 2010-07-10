#include <stdarg.h>

#define ALIGN(x, a)	(((x) + (a) - 1) & ~((a) - 1))

void *__va_arg(void **ap, int size)
{
	void *ret = *ap;
	*ap += ALIGN(size, 4);
	return ret;
}
