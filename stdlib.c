#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

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
