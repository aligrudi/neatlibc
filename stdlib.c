#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ATEXIT_MAX		32

char **environ;

void exit(int status)
{
	_exit(status);
}

int abs(int n)
{
	return n >= 0 ? n : -n;
}

long labs(long n)
{
	return n >= 0 ? n : -n;
}

char *getenv(char *name)
{
	char **p = environ;
	int len = strlen(name);
	for (; *p; p++)
		if (!memcmp(name, *p, len) && (*p)[len] == '=')
			return *p + len + 1;
	return NULL;
}

int system(char *cmd)
{
	char *argv[] = {"/bin/sh", "-c", cmd, NULL};
	pid_t pid;
	int ret;
	pid = fork();
	if (pid < 0)
		return -1;
	if (!pid) {
		execv(argv[0], argv);
		exit(1);
	}
	if (waitpid(pid, &ret, 0) != pid)
		return -1;
	return ret;
}

static void (*atexit_func[ATEXIT_MAX])(void);
static int atexit_cnt;

int atexit(void (*func)(void))
{
	if (atexit_cnt >= ATEXIT_MAX)
		return -1;
	atexit_func[atexit_cnt++] = func;
	return 0;
}

void __neatlibc_exit(void)
{
	int i;
	for (i = 0; i < atexit_cnt; i++)
		atexit_func[i]();
}
