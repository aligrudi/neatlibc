#include <stdlib.h>
#include <string.h>

char **environ;

void exit(int status)
{
	_exit(status);
}

int abs(int n)
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
