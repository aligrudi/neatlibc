#include <ctype.h>
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

int fputc(int c, FILE *fp)
{
	if (fp->olen < fp->osize) {
		fp->obuf[fp->olen++] = c;
		fp->ostat++;
	}
	if (c == '\n' || fp->olen == fp->osize)
		if (fflush(fp))
			return EOF;
	return c;
}

int putchar(int c)
{
	return fputc(c, stdout);
}

static void ostr(FILE *fp, char *s, int wid)
{
	int fill = wid - strlen(s);
	while (fill-- > 0)
		fputc(' ', fp);
	while (*s)
		fputc((unsigned char) *s++, fp);
}

static int digits(unsigned long n, int base)
{
	int i;
	for (i = 0; n; i++)
		n /= base;
	return i ? i : 1;
}

static char *digs = "0123456789abcdef";
static char *digs_uc = "0123456789ABCDEF";

#define FMT_LEFT	0001	/* flag '-' */
#define FMT_PLUS	0002	/* flag '+' */
#define FMT_BLANK	0004	/* flag ' ' */
#define FMT_ALT		0010	/* flag '#' */
#define FMT_ZERO	0020	/* flag '0' */
#define FMT_SIGNED	0040	/* is the conversion signed? */
#define FMT_UCASE	0100	/* uppercase hex digits? */

static void oint(FILE *fp, unsigned long n, int base,
		int wid, int bytes, int flags)
{
	char buf[64];
	char *s = buf;
	int neg = 0;
	int sign = '\0';
	char fill;
	int left = flags & FMT_LEFT;
	int alt_form = flags & FMT_ALT;
	int ucase = flags & FMT_UCASE;
	int prefix_len = 0; /* length of sign or base prefix */
	int d;
	int i;
	if (flags & FMT_SIGNED) {
		if ((signed long) n < 0) {
			neg = 1;
			sign = '-';
			n = -n;
		} else {
			if (flags & FMT_PLUS)
				sign = '+';
			else if (flags & FMT_BLANK)
				sign = ' ';
		}
		prefix_len = !!sign;
	} else if (n > 0 && alt_form) {
		prefix_len = base == 16 ? 2 : 1;
	}
	if (bytes == 1)
		n &= 0x000000ff;
	if (bytes == 2)
		n &= 0x0000ffff;
	if (bytes == 4)
		n &= 0xffffffff;
	d = digits(n, base);
	for (i = 0; i < d; i++) {
		s[d - i - 1] = ucase ? digs_uc[n % base] : digs[n % base];
		n /= base;
	}
	s[d] = '\0';
	fill = (flags & FMT_ZERO) ? '0' : ' ';
	i = d + prefix_len;
	if (fill == ' ' && !left)
		while (i++ < wid)
			fputc(' ', fp);
	if (sign) {
		fputc(sign, fp);
	} else if (prefix_len) {
		fputc('0', fp);
		if (base == 16)
			fputc(ucase ? 'X' : 'x', fp);
	}
	if (fill == '0' && !left)
		while (i++ < wid)
			fputc('0', fp);
	ostr(fp, buf, 0);
	if (left)
		while (i++ < wid)
			fputc(' ', fp);
}

static char *fmt_flags = "-+ #0";

int vfprintf(FILE *fp, char *fmt, va_list ap)
{
	char *s = fmt;
	int beg = fp->ostat;
	while (*s) {
		int c = (unsigned char) *s++;
		int wid = 0;
		int bytes = sizeof(int);
		int flags = 0;
		char *f;
		if (c != '%') {
			fputc(c, fp);
			continue;
		}
		while ((f = strchr(fmt_flags, *s))) {
			flags |= 1 << (f - fmt_flags);
			s++;
		}
		while (isdigit(*s)) {
			wid *= 10;
			wid += *s++ - '0';
		}
		while (*s == 'l') {
			bytes = sizeof(long);
			s++;
		}
		while (*s == 'h') {
			bytes = bytes < sizeof(int) ? sizeof(char) : sizeof(short);
			s++;
		}
		switch ((c = *s++)) {
		case 'd': case 'i':
			flags |= FMT_SIGNED;
			oint(fp, va_arg(ap, long), 10, wid, bytes, flags);
			break;
		case 'u':
			oint(fp, va_arg(ap, long), 10, wid, bytes, flags);
			break;
		case 'o':
			oint(fp, va_arg(ap, long), 8, wid, bytes, flags);
			break;
		case 'x':
		case 'p':
			oint(fp, va_arg(ap, long), 16, wid, bytes, flags);
			break;
		case 'X':
			flags |= FMT_UCASE;
			oint(fp, va_arg(ap, long), 16, wid, bytes, flags);
			break;
		case 'c':
			fputc(va_arg(ap, int), fp);
			break;
		case 's':
			ostr(fp, va_arg(ap, char *), wid);
			break;
		case '\0':
			s--;
			break;
		default:
			fputc(c, fp);
		}
	}
	return fp->ostat - beg;
}

void perror(char *s)
{
	int idx = errno;
	if (idx >= sys_nerr)
		idx = 0;
	if (s && *s)
		fprintf(stderr, "%s: %s\n", s, sys_errlist[idx]);
	else
		fprintf(stderr, "%s\n", sys_errlist[idx]);
}

int vsnprintf(char *dst, int sz, char *fmt, va_list ap)
{
	FILE f = {-1, EOF};
	int ret;
	f.obuf = dst;
	f.osize = sz - 1;
	ret = vfprintf(&f, fmt, ap);
	dst[f.olen] = '\0';
	return ret;
}

int vsprintf(char *dst, char *fmt, va_list ap)
{
	return vsnprintf(dst, 1 << 20, fmt, ap);
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

int vprintf(char *fmt, va_list ap)
{
	return vfprintf(stdout, fmt, ap);
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

int snprintf(char *dst, int sz, char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vsnprintf(dst, sz, fmt, ap);
	va_end(ap);
	return ret;
}

int fputs(char *s, FILE *fp)
{
	while (*s)
		fputc((unsigned char) *s++, fp);
	return 0;
}

int puts(char *s)
{
	int ret = fputs(s, stdout);
	if (ret >= 0)
		fputc('\n', stdout);
	return ret;
}

long fwrite(void *v, long sz, long n, FILE *fp)
{
	unsigned char *s = v;
	int i = n * sz;
	while (i-- > 0)
		if (fputc(*s++, fp) == EOF)
			return n * sz - i - 1;
	return n * sz;
}
