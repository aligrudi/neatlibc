#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

time_t time(time_t *t)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	if (t)
		*t = tv.tv_sec;
	return tv.tv_sec;
}
