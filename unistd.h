#include <stddef.h>

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

#define R_OK		4
#define W_OK		2
#define X_OK		1
#define F_OK		0
int access(char *name, int type);

extern char **environ;

int close(int fd);
int write(int fd, void *buf, int n);
int read(int fd, void *buf, int n);

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2
long lseek(int fd, long offset, int whence);

void _exit(int status);
int execve(char *path, char *argv[], char *envp[]);
int execle(char *path, ...);
int sleep(int n);
