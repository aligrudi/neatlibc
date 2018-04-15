#include <stdarg.h>

#define EOF		(-1)
#define getc(fp)	(fgetc(fp))

typedef struct {
	int fd;
	int back;		/* pushback buffer */
	char *ibuf, *obuf;	/* input/output buffer */
	int isize, osize;	/* ibuf size */
	int ilen, olen;		/* length of data in buf */
	int iown, oown;		/* free the buffer when finished */
	int icur;		/* current position in ibuf */
	int ostat;
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

FILE *fopen(char *path, char *mode);
int fclose(FILE *fp);
int fflush(FILE *fp);
void setbuf(FILE *fp, char *buf);

int printf(char *fmt, ...);
int vprintf(char *fmt, va_list ap);
int fprintf(FILE *fp, char *fmt, ...);
int sprintf(char *dst, char *fmt, ...);
int vsprintf(char *dst, char *fmt, va_list ap);
int vfprintf(FILE *fp, char *fmt, va_list ap);
int snprintf(char *dst, int sz, char *fmt, ...);
int vsnprintf(char *dst, int sz, char *fmt, va_list ap);
int fputs(char *s, FILE *fp);
int puts(char *s);

int fgetc(FILE *fp);
char *fgets(char *s, int sz, FILE *fp);
int scanf(char *fmt, ...);
int fscanf(FILE *fp, char *fmt, ...);
int sscanf(char *s, char *fmt, ...);
int vsscanf(char *s, char *fmt, va_list ap);
int vfscanf(FILE *fp, char *fmt, va_list ap);
int getchar(void);
int ungetc(int c, FILE *fp);
long fwrite(void *s, long sz, long n, FILE *fp);
long fread(void *s, long sz, long n, FILE *fp);

void perror(char *s);
