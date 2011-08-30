#include <stddef.h>

void *malloc(int n);
void free(void *m);

int atoi(char *s);
long atol(char *s);
int abs(int n);

void exit(int status);
void abort(void);
char *getenv(char *name);
void qsort(void *a, int n, int sz, int (*cmp)(void *, void *));
int mkstemp(char *t);
