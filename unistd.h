#include <stddef.h>

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

extern char **environ;

int close(int fd);
int write(int fd, void *buf, int n);
int read(int fd, void *buf, int n);
void _exit(int status);

#define R_OK		4
#define W_OK		2
#define X_OK		1
#define F_OK		0

int access(char *name, int type);
