#define WNOHANG		0x00000001
#define WUNTRACED	0x00000002

#define WSTOPPED	0x00000002
#define WEXITED		0x00000004
#define WCONTINUED	0x01000000

#define WEXITSTATUS(s)	(((s) & 0xff00) >> 8)
#define WTERMSIG(s)	((s) & 0x7f)
#define WSTOPSIG(s)	WEXITSTATUS(s)
#define WCOREDUMP(s)	((s) & 0x80)
#define WIFEXITED(s)	(WTERMSIG(s) == 0)
#define WIFSTOPPED(s)	(((s) & 0xff) == 0x7f)
#define WIFSIGNALED(s)	(!WIFEXITED(s) && !WIFSTOPPED(s))
#define WIFCONTINUED(s)	((s) == 0xffff)

int wait(int *status);
int waitpid(int pid, int *status, int options);
