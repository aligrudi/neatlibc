#include <string.h>

char *strncpy(char *d, char *s, long n)
{
	int len = strlen(s);
	if (len > n)
		len = n;
	memcpy(d, s, len);
	memset(d + len, 0, n - len);
	return d;
}

char *strcat(char *d, char *s)
{
	strcpy(d + strlen(d), s);
	return d;
}

char *strstr(char *s, char *r)
{
	int len = strlen(r);
	if (!len)
		return s;
	while (s) {
		if (!memcmp(s, r, len))
			return s;
		s = strchr(s + 1, *r);
	}
	return NULL;
}
