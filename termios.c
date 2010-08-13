#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>

int tcgetattr(int fd, struct termios *term)
{
	return ioctl(fd, TCGETS, term);
}

int tcsetattr(int fd, int actions, struct termios* term)
{
	switch (actions) {
	case TCSANOW:
		return ioctl(fd, TCSETS , term);
	case TCSADRAIN:
		return ioctl(fd, TCSETSW, term);
	case TCSAFLUSH:
		return ioctl(fd, TCSETSF, term);
	}
	errno = EINVAL;
	return -1;
}
