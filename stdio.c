#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *putstr(char *d, char *s)
{
	while (*s)
		*d++ = *s++;
	return d;
}

static int digits(unsigned long n, int base)
{
	int i;
	for (i = 0; n; i++)
		n /= base;
	return i ? i : 1;
}

static char *digs = "0123456789abcdef";

static char *putint(char *s, unsigned long n, int base, int sign)
{
	int d;
	int i;
	if (sign && (signed long) n < 0) {
		*s++ = '-';
		n = -n;
	}
	d = digits(n, base);
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
		if (*s == 'l')
			s++;
		switch ((c = *s++)) {
		case 'd':
			d = putint(d, va_arg(ap, long), 10, 1);
			break;
		case 'u':
			d = putint(d, va_arg(ap, long), 10, 0);
			break;
		case 'x':
		case 'p':
			d = putint(d, va_arg(ap, long), 16, 0);
			break;
		case 'c':
			*d++ = va_arg(ap, int);
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

static char buf[1 << 14];

static FILE _stdout = {1};
static FILE _stderr = {2};
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;

int printf(char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vsprintf(buf, fmt, ap);
	va_end(ap);
	return write(1, buf, ret);
}

int fprintf(FILE *filp, char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vsprintf(buf, fmt, ap);
	va_end(ap);
	return write(filp->fd, buf, ret);
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

void perror(char *s)
{
	int idx = errno;
	if (idx >= sys_nerr)
		idx = 0;
	fprintf(stderr, "%s: %s\n", s, sys_errlist[idx]);
}

FILE *fopen(char *path, char *mode)
{
	FILE *fp;
	int flags;

	if (strchr(mode, '+'))
		flags = O_RDWR;
	else
		flags = *mode == 'r' ? O_RDONLY : O_WRONLY;
	if (*mode != 'r')
		flags |= O_CREAT;
	if (*mode == 'w')
		flags |= O_TRUNC;
	if (*mode == 'a')
		flags |= O_APPEND;

	fp = malloc(sizeof(*fp));
	fp->fd = open(path, flags, 0600);
	return fp;
}

int fclose(FILE *fp)
{
	int ret = close(fp->fd);
	free(fp);
	return ret;
}

void setbuf(FILE *fp, char *buf)
{
}
