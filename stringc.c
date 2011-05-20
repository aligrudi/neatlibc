#include <string.h>

char *strncpy(char *d, char *s, int n)
{
	int len = strlen(s);
	if (len > n)
		len = n;
	memcpy(d, s, len);
	memcpy(d + len, 0, n - len);
	return d;
}

char *strcat(char *d, char *s)
{
	strcpy(d + strlen(d), s);
	return d;
}

int strncmp(char *d, char *s, int n)
{
	int len = strlen(d);
	if (len >= n)
		len = n - 1;
	return memcmp(d, s, len + 1);
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
