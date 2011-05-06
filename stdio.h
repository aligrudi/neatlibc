#include <stdarg.h>

typedef struct {
	int fd;
} FILE;

extern FILE *stdout;
extern FILE *stderr;

int printf(char *fmt, ...);
int fprintf(FILE *filp, char *fmt, ...);
int sprintf(char *dst, char *fmt, ...);
int vsprintf(char *dst, char *fmt, va_list ap);

void perror(char *s);
