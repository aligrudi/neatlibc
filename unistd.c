#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int sleep(int n)
{
	struct timespec req = {n, 0};
	struct timespec rem;
	if (nanosleep(&req, &rem))
		return rem.tv_sec;
	return 0;
}

#define EXECARGS	(1 << 7)

int execle(char *path, ...)
{
	va_list ap;
	char *argv[EXECARGS];
	char **envp;
	int argc = 0;
	va_start(ap, path);
	while (argc + 1 < EXECARGS && (argv[argc] = va_arg(ap, char *)))
		argc++;
	envp = va_arg(ap, char **);
	va_end(ap);
	argv[argc] = NULL;
	execve(path, argv, envp);
	return -1;
}

int execvp(char *cmd, char *argv[])
{
	char path[512];
	char *p = getenv("PATH");
	if (strchr(cmd, '/'))
		return execve(cmd, argv, environ);
	if (!p)
		p = "/bin";
	while (*p) {
		char *s = path;
		while (*p && *p != ':')
			*s++ = *p++;
		if (s != path)
			*s++ = '/';
		strcpy(s, cmd);
		execve(path, argv, environ);
		if (*p == ':')
			p++;
	}
	return -1;
}

int wait(int *status)
{
	return waitpid(-1, status, 0);
}

int raise(int sig)
{
	return kill(getpid(), sig);
}

void abort(void)
{
	raise(SIGABRT);
	while (1)
		;
}
