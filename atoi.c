#include <stdlib.h>

int atoi(char *s)
{
	int num = 0;
	int neg = 0;
	while (*s == ' ')
		s++;
	if (*s == '-' || *s == '+')
		neg = *s++ == '-';
	while ((unsigned) (*s - '0') <= 9u)
		num = num * 10 + *s++ - '0';
	return neg ? -num : num;
}

long atol(char *s)
{
	return atoi(s);
}
