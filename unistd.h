#include <stddef.h>

extern char **environ;

int close(int fd);
int write(int fd, void *buf, int n);
int read(int fd, int *buf, int n);
void _exit(int status);
