#include <stddef.h>

void *memcpy(void *dst, void *src, int n);
void *memmove(void *dst, void *src, int n);
void *memset(void *s, int v, int n);
void *memchr(void *s, int c, int n);

char *strcpy(char *dst, char *src);
char *strchr(char *s, int c);
int strlen(char *s);
int strcmp(char *s1, char *s2);

char *strncpy(char *d, char *s, int n);
char *strcat(char *d, char *s);
int strncmp(char *d, char *s, int n);
char *strstr(char *s, char *r);
