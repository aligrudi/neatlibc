#include <stdlib.h>
#include <string.h>

char **environ;

int exit(int status)
{
	return _exit(status);
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
