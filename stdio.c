#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSZ		1024

static char _ibuf[BUFSZ], _obuf[BUFSZ], _ebuf[BUFSZ];
static FILE _stdin = {0, EOF, _ibuf, NULL, BUFSZ, 0};
static FILE _stdout = {1, EOF, NULL, _obuf, 0, BUFSZ};
static FILE _stderr = {2, EOF, NULL, _ebuf, 0, 1};
FILE *stdin = &_stdin;
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;

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
	memset(fp, 0, sizeof(*fp));
	fp->fd = open(path, flags, 0600);
	if (fp->fd < 0) {
		free(fp);
		return NULL;
	}
	fp->back = EOF;
	fp->ibuf = malloc(BUFSZ);
	fp->obuf = malloc(BUFSZ);
	fp->isize = BUFSZ;
	fp->osize = BUFSZ;
	fp->iown = 1;
	fp->oown = 1;
	return fp;
}

int fclose(FILE *fp)
{
	int ret = close(fp->fd);
	if (fp->iown)
		free(fp->ibuf);
	if (fp->oown)
		free(fp->obuf);
	free(fp);
	return ret;
}

int fflush(FILE *fp)
{
	if (fp->fd < 0)
		return 0;
	if (write(fp->fd, fp->obuf, fp->olen) != fp->olen)
		return EOF;
	fp->olen = 0;
	return 0;
}

static int oc(FILE *fp, int c)
{
	if (fp->olen < fp->osize) {
		fp->obuf[fp->olen++] = c;
		fp->ostat++;
	}
	if (c == '\n' || fp->olen == fp->osize)
		fflush(fp);
	return c;
}

static void ostr(FILE *fp, char *s, int wid)
{
	int fill = wid - strlen(s);
	while (fill-- > 0)
		oc(fp, ' ');
	while (*s)
		oc(fp, *s++);
}

static int digits(unsigned long n, int base)
{
	int i;
	for (i = 0; n; i++)
		n /= base;
	return i ? i : 1;
}

static char *digs = "0123456789abcdef";

static void oint(FILE *fp, unsigned long n, int base, int sign, int wid, int fill)
{
	char buf[64];
	char *s = buf;
	int neg = 0;
	int d;
	int i;
	if (sign && (signed long) n < 0) {
		neg = 1;
		n = -n;
	}
	d = digits(n, base);
	for (i = 0; i < d; i++) {
		s[d - i - 1] = digs[n % base];
		n /= base;
	}
	s[d] = '\0';
	for (i = d + neg; i < wid; i++)
		oc(fp, fill);
	if (neg)
		oc(fp, '-');
	ostr(fp, buf, 0);
}

int vfprintf(FILE *fp, char *fmt, va_list ap)
{
	char *s = fmt;
	int beg = fp->ostat;
	while (*s) {
		int c = *s++;
		int fill = ' ';
		int wid = 0;
		if (c != '%') {
			oc(fp, c);
			continue;
		}
		if (*s == 'l')
			s++;
		if (*s == '0') {
			fill = '0';
			s++;
		}
		while (isdigit(*s)) {
			wid *= 10;
			wid += *s++ - '0';
		}
		switch ((c = *s++)) {
		case 'd':
			oint(fp, va_arg(ap, long), 10, 1, wid, fill);
			break;
		case 'u':
			oint(fp, va_arg(ap, long), 10, 0, wid, fill);
			break;
		case 'x':
		case 'p':
			oint(fp, va_arg(ap, long), 16, 0, wid, fill);
			break;
		case 'c':
			oc(fp, va_arg(ap, int));
			break;
		case 's':
			ostr(fp, va_arg(ap, char *), wid);
			break;
		case '\0':
			s--;
			break;
		default:
			oc(fp, c);
		}
	}
	return fp->ostat - beg;
}

void perror(char *s)
{
	int idx = errno;
	if (idx >= sys_nerr)
		idx = 0;
	fprintf(stderr, "%s: %s\n", s, sys_errlist[idx]);
}

int vsprintf(char *dst, char *fmt, va_list ap)
{
	FILE f = {-1, EOF};
	int ret;
	f.obuf = dst;
	f.osize = 1 << 20;
	ret = vfprintf(&f, fmt, ap);
	dst[f.olen] = '\0';
	return ret;
}

int printf(char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vfprintf(stdout, fmt, ap);
	va_end(ap);
	return ret;
}

int fprintf(FILE *fp, char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vfprintf(fp, fmt, ap);
	va_end(ap);
	return ret;
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
