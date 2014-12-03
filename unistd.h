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
int unlink(char *path);

extern char **environ;

int close(int fd);
long write(int fd, void *buf, long n);
long read(int fd, void *buf, long n);

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2
long lseek(int fd, long offset, int whence);

void _exit(int status);
int fork(void);
int getpid(void);
int getppid(void);
int execve(char *path, char *argv[], char *envp[]);
int execle(char *path, ...);
int execvp(char *file, char *argv[]);
int execv(char *path, char *argv[]);
int sleep(int n);
