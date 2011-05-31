struct timespec {
	long tv_sec;
	long tv_nsec;
};

int nanosleep(struct timespec *req, struct timespec *rem);

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	long tm_gmtoff;
	char *tm_zone;
};

long time(long *timep);
int strftime(char *s, int len, char *fmt, struct tm *tm);
struct tm *localtime(long *timep);
struct tm *gmtime(long *timep);

extern long timezone;
void tzset(void);
