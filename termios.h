#include <sys/cdefs.h>
#include <sys/types.h>

struct winsize {
	unsigned short ws_row;
	unsigned short ws_col;
	unsigned short ws_xpixel;
	unsigned short ws_ypixel;
};

struct termios {
	unsigned c_iflag;
	unsigned c_oflag;
	unsigned c_cflag;
	unsigned c_lflag;
	unsigned char cc_t c_line;
	unsigned char c_cc[19];
};

#define ISIG		0000001
#define ICANON		0000002
#define XCASE		0000004
#define ECHO		0000010
#define ECHOE		0000020
#define ECHOK		0000040
#define ECHONL		0000100
#define NOFLSH		0000200
#define ECHOCTL		0001000
#define ECHOPRT		0002000
#define ECHOKE		0004000

#define TCSANOW		0
#define TCSADRAIN	1
#define TCSAFLUSH	2

int tcgetattr(int fd, struct termios *term);
int tcsetattr(int fd, int actions, struct termios *term);
