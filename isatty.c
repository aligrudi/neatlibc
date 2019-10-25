#include <termios.h>
#include <sys/ioctl.h>

int
isatty(int fd)
{
	struct termios dummy;

	return (!ioctl(fd, TCGETS, &dummy));
}
