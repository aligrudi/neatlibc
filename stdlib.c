#include <stdlib.h>

char **environ;

int exit(int status)
{
	return _exit(status);
}
