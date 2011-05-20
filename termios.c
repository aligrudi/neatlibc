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

void cfmakeraw(struct termios *t)
{
	t->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP |
			INLCR | IGNCR | ICRNL | IXON);
	t->c_oflag &= ~OPOST;
	t->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	t->c_cflag &= ~(CSIZE | PARENB);
	t->c_cflag |= CS8;
	t->c_cc[VMIN] = 1;
	t->c_cc[VTIME] = 0;
}
