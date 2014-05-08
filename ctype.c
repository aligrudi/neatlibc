#include <ctype.h>

int isascii(int c)
{
	return (unsigned) c < 128u;
}

int isblank(int c)
{
	return c == ' ' || c == '\t';
}

int isalpha(int c)
{
	return (unsigned) ((c | 0x20) - 'a') < 26u;
}

int isdigit(int c)
{
	return (unsigned) (c - '0') < 10u;
}

int isalnum(int c)
{
	return (unsigned) ((c | 0x20) - 'a') < 26u ||
		(unsigned) (c - '0') < 10u;
}

int isspace(int c)
{
	return (unsigned) (c - 9) < 5u || c == ' ';
}

int isupper(int c)
{
	return (unsigned) (c - 'A') < 26u;
}

int islower(int c)
{
	return (unsigned) (c - 'a') < 26u;
}

int tolower(int c)
{
	return (unsigned) (c - 'A') < 26u ? c + ('a' - 'A') : c;
}

int toupper(int c)
{
	return (unsigned) (c - 'a') < 26u ? c + ('A' - 'a') : c;
}

int isprint(int c)
{
	return (c & 0x7f) >= 32 && c < 127;
}

int ispunct(int c)
{
	return isprint(c) && !isalnum(c) && !isspace(c);
}
