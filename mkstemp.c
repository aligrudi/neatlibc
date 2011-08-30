#include <fcntl.h>
#include <string.h>

static int tmpid;
static char *digs = "0123456789abcdef";

int mkstemp(char *t)
{
	char *x = t + strlen(t) - 6;
	int fd;
	int i;
	if (strlen(t) < 6)
		return -1;
	for (i = 0; i < 6; i++)
		x[i] = '0';
	while ((fd = open(t, O_RDWR | O_EXCL | O_CREAT, 0600)) == -1) {
		int n = ++tmpid;
		for (i = 0; i < 6; i++) {
			x[5 - i] = digs[n & 0x0f];
			n <<= 4;
		}
	}
	unlink(t);
	return fd;
}
