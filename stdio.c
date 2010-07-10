#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

static char *putstr(char *d, char *s)
{
	while (*s)
		*d++ = *s++;
	return d;
}

static int digits(long n, int base)
{
	int i;
	for (i = 0; n; i++)
		n /= base;
	return i ? i : 1;
}

static char *digs = "0123456789abcdef";

static char *putint(char *s, long n, int base)
{
	int i;
	int d = digits(n, base);
	for (i = 0; i < d; i++) {
		s[d - i - 1] = digs[n % base];
		n /= base;
	}
	return s + d;
}

int vsprintf(char *dst, char *fmt, va_list ap)
{
	char *d = dst;
	char *s = fmt;
	while (*s) {
		int c = *s++;
		if (c != '%') {
			*d++ = c;
			continue;
		}
		switch ((c = *s++)) {
		case 'd':
			d = putint(d, va_arg(ap, long), 10);
			break;
		case 'x':
			d = putint(d, va_arg(ap, long), 16);
			break;
		case 's':
			d = putstr(d, va_arg(ap, char *));
			break;
		case '\0':
			s--;
			break;
		default:
			*d++ = c;
		}
	}
	*d = '\0';
	return d - dst;
}

static char buf[1 << 12];

int printf(char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vsprintf(buf, fmt, ap);
	va_end(ap);
	return write(1, buf, ret);
}

int sprintf(char *dst, char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vsprintf(dst, fmt, ap);
	va_end(ap);
	return ret;
}
