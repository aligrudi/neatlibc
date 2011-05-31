#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

static char *wday_ab[] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};
static char *wday[] = {
	"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};
static char *mon_ab[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
static char *mon[] = {
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};

static char *putstr(char *d, char *s)
{
	while (*s)
		*d++ = *s++;
	return d;
}

static char *puti(char *s, unsigned long n, int wid, int zpad)
{
	int i;
	for (i = wid - 1; i >= 0; i--) {
		if (!n) {
			if (!zpad && i < wid - 1)
				s[i] = ' ';
			else
				s[i] = '0';
		} else {
			s[i] = '0' + n % 10;
			n /= 10;
		}
	}
	return s + wid;
}

static char *puttz(char *s)
{
	int d = timezone / 60;
	if (d < 0) {
		*s++ = '+';
		d = -d;
	} else {
		*s++ = '-';
	}
	s = puti(s, d / 60, 2, 1);
	s = puti(s, d % 60, 2, 1);
	return s;
}

int strftime(char *s, int n, char *f, struct tm *tm)
{
	int val;
	char *beg = s;
	char *e = s + n;
	while (s + 1 < e && *f) {
		int c = *f++;
		if (c != '%') {
			*s++ = c;
			continue;
		}
		c = *f++;
		switch (c) {
		case '%':
			*s++ = '%';
			break;
		case 'a':
			s = putstr(s, wday_ab[tm->tm_wday]);
			break;
		case 'A':
			s = putstr(s, wday[tm->tm_wday]);
			break;
		case 'b':
		case 'h':
			s = putstr(s, mon_ab[tm->tm_mon]);
			break;
		case 'B':
			s = putstr(s, mon[tm->tm_mon]);
			break;
		case 'c':
			s += strftime(s, e - s, "%b %a %d %k:%M:%S %Z %Y", tm);
			break;
		case 'C':
			s = puti(s, (1900 + tm->tm_year) / 100, 2, 1);
			break;
		case 'd':
			s = puti(s, tm->tm_mday, 2, 1);
			break;
		case 'D':
			s += strftime(s, e - s, "%m/%d/%y", tm);
			break;
		case 'e':
			s = puti(s, tm->tm_mday, 2, 0);
			break;
		case 'F':
			s += strftime(s, e - s, "%Y/%m/%d", tm);
			break;
		case 'H':
			s = puti(s, tm->tm_hour, 2, 1);
			break;
		case 'I':
			val = tm->tm_hour > 12 ? tm->tm_hour - 12 : tm->tm_hour;
			s = puti(s, val ? val : 12, 2, 1);
			break;
		case 'j':
			s = puti(s, tm->tm_yday + 1, 3, 1);
			break;
		case 'k':
			s = puti(s, tm->tm_hour, 2, 1);
			break;
		case 'm':
			s = puti(s, tm->tm_mon + 1, 2, 1);
			break;
		case 'M':
			s = puti(s, tm->tm_min, 2, 1);
			break;
		case 'n':
			*s++ = '\n';
			break;
		case 'p':
			s = putstr(s, tm->tm_hour >= 12 ? "PM" : "AM");
			break;
		case 'P':
			s = putstr(s, tm->tm_hour >= 12 ? "pm" : "am");
			break;
		case 'r':
			s += strftime(s, e - s, "%I:%M:%S %p", tm);
			break;
		case 'R':
			s += strftime(s, e - s, "%H:%M", tm);
			break;
		case 'S':
			s = puti(s, tm->tm_sec, 2, 1);
			break;
		case 't':
			*s++ = '\t';
			break;
		case 'T':
			s += strftime(s, e - s, "%H:%M:%S", tm);
			break;
		case 'u':
			s = puti(s, tm->tm_wday ? tm->tm_wday : 7, 1, 0);
			break;
		case 'w':
			s = puti(s, tm->tm_wday, 1, 0);
			break;
		case 'x':
			s += strftime(s, e - s, "%b %a %d", tm);
			break;
		case 'X':
			s += strftime(s, e - s, "%k:%M:%S", tm);
			break;
		case 'y':
			s = puti(s, tm->tm_year % 100, 2, 1);
			break;
		case 'Y':
			s = puti(s, 1900 + tm->tm_year, 4, 1);
			break;
		case 'z':
			s = puttz(s);
			break;
		default:
			break;
		}
	}
	*s = '\0';
	return s - beg;
}
