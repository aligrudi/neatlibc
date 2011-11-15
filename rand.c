#include <stdlib.h>

static unsigned r;

void srand(unsigned int seed)
{
	r = seed;
}

int rand(void)
{
	r = r * 1103515245 + 12345;
	return r & 0x7fffffff;
}
