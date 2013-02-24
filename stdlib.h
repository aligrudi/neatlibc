#include <stddef.h>

#define RAND_MAX		0x7fffffff

void *malloc(long n);
void free(void *m);

int atoi(char *s);
long atol(char *s);
int abs(int n);
long labs(long n);

void exit(int status);
void abort(void);
char *getenv(char *name);
void qsort(void *a, int n, int sz, int (*cmp)(void *, void *));
int mkstemp(char *t);

void srand(unsigned int seed);
int rand(void);
