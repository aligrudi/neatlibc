#include <stddef.h>

#define RAND_MAX		0x7fffffff

void *malloc(long n);
void free(void *m);
void *calloc(long n, long sz);

int atoi(char *s);
long atol(char *s);
int abs(int n);
long labs(long n);

void exit(int status);
void abort(void);
int atexit(void (*func)(void));

char *getenv(char *name);
void qsort(void *a, int n, int sz, int (*cmp)(void *, void *));
int mkstemp(char *t);
int system(char *cmd);

void srand(unsigned int seed);
int rand(void);

/* for examining heap memory allocation */
#ifdef MEMTST
void *memtst_malloc(long n);
void memtst_free(void *v);
void *memtst_calloc(long n, long sz);
#define malloc	memtst_malloc
#define free	memtst_free
#define calloc	memtst_calloc
#endif
