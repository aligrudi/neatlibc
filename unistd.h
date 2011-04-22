#include <stddef.h>

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

extern char **environ;

int close(int fd);
int write(int fd, void *buf, int n);
int read(int fd, void *buf, int n);
void _exit(int status);
