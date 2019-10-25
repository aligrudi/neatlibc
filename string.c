#include <stdlib.h>
#include <string.h>

char *strdup(const char *s)
{
	size_t n = strlen(s) + 1;
	char *res = malloc(n);
	if (res)
		memcpy(res, s, n);
	return res;
}
