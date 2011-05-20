#include <time.h>
#include <unistd.h>
#include <stdarg.h>

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
	char **env;
	int argc = 0;
	va_start(ap, path);
	while (argc + 1 < EXECARGS && (argv[argc] = va_arg(ap, char *)))
		argc++;
	env = va_arg(ap, char **);
	va_end(ap);
	argv[argc] = NULL;
	execve(path, argv, env);
}

int wait(int *status)
{
	return waitpid(-1, status, 0);
}
