#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static int ic(FILE *fp)
{
	int nr;
	if (fp->back != EOF) {
		int i = fp->back;
		fp->back = EOF;
		return i;
	}
	while (fp->fd >= 0 && fp->icur == fp->ilen) {
		int nr = read(fp->fd, fp->ibuf, fp->isize);
		if (nr <= 0)
			break;
		fp->ilen = nr;
		fp->icur = 0;
	}
	return fp->icur < fp->ilen ? (unsigned char) fp->ibuf[fp->icur++] : EOF;
}

void setbuf(FILE *fp, char *buf)
{
}

int fgetc(FILE *fp)
{
	return ic(fp);
}

int getchar(void)
{
	return ic(stdin);
}

int ungetc(int c, FILE *fp)
{
	if (fp->back == EOF)
		fp->back = c;
	return fp->back;
}

/* t is 1 for char, 2 for short, 4 for int, and 8 for long */
static int iint(FILE *fp, void *dst, int t)
{
	long n = 0;
	int c;
	int neg = 0;
	c = ic(fp);
	if (c == '-')
		neg = 1;
	if (c == '-' || c == '+')
		c = ic(fp);
	if (!isdigit(c)) {
		ungetc(c, fp);
		return 1;
	}
	do {
		n = n * 10 + c - '0';
	} while (isdigit(c = ic(fp)));
	ungetc(c, fp);
	if (t == 8)
		*(long *) dst = neg ? -n : n;
	else if (t == 4)
		*(int *) dst = neg ? -n : n;
	else if (t == 2)
		*(short *) dst = neg ? -n : n;
	else
		*(char *) dst = neg ? -n : n;
	return 0;
}

static int istr(FILE *fp, char *dst)
{
	char *d = dst;
	int c;
	while ((c = ic(fp)) != EOF && !isspace(c))
		*d++ = c;
	*d = '\0';
	ungetc(c, fp);
	return d == dst;
}

int vfscanf(FILE *fp, char *fmt, va_list ap)
{
	int ret = 0;
	int t, c;
	while (*fmt) {
		while (isspace(*fmt))
			fmt++;
		while (isspace(c = ic(fp)))
			;
		ungetc(c, fp);
		while (*fmt && *fmt != '%' && !isspace(*fmt))
			if (*fmt++ != ic(fp))
				return ret;
		if (*fmt != '%')
			continue;
		fmt++;
		t = sizeof(int);
		while (*fmt == 'l') {
			t = sizeof(long);
			fmt++;
		}
		while (*fmt == 'h') {
			t = t < sizeof(int) ? sizeof(char) : sizeof(short);
			fmt++;
		}
		switch (*fmt++) {
		case 'u':
		case 'd':
			if (iint(fp, va_arg(ap, long *), t))
				return ret;
			ret++;
			break;
		case 's':
			if (istr(fp, va_arg(ap, char *)))
				return ret;
			ret++;
			break;
		}
	}
	return ret;
}

int fscanf(FILE *fp, char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vfscanf(fp, fmt, ap);
	va_end(ap);
	return ret;
}

int scanf(char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vfscanf(stdin, fmt, ap);
	va_end(ap);
	return ret;
}

int vsscanf(char *s, char *fmt, va_list ap)
{
	FILE f = {-1, EOF};
	f.ibuf = s;
	f.ilen = strlen(s);
	return vfscanf(&f, fmt, ap);
}

int sscanf(char *s, char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vsscanf(s, fmt, ap);
	va_end(ap);
	return ret;
}

char *fgets(char *s, int sz, FILE *fp)
{
	int i = 0;
	int c;
	while (i + 1 < sz && (c = ic(fp)) != EOF) {
		s[i++] = c;
		if (c == '\n')
			break;
	}
	s[i] = '\0';
	return i ? s : NULL;
}
