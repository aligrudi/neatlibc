#define NSIG		32

#define SIGHUP		 1
#define SIGINT		 2
#define SIGQUIT		 3
#define SIGILL		 4
#define SIGTRAP		 5
#define SIGABRT		 6
#define SIGIOT		 6
#define SIGFPE		 8
#define SIGKILL		 9
#define SIGSEGV		11
#define SIGPIPE		13
#define SIGALRM		14
#define SIGTERM		15
#define SIGUNUSED	31
#define SIGBUS		 7
#define SIGUSR1		10
#define SIGUSR2		12
#define SIGSTKFLT	16
#define SIGCHLD		17
#define SIGCONT		18
#define SIGSTOP		19
#define SIGTSTP		20
#define SIGTTIN		21
#define SIGTTOU		22
#define SIGURG		23
#define SIGXCPU		24
#define SIGXFSZ		25
#define SIGVTALRM	26
#define SIGPROF		27
#define SIGWINCH	28
#define SIGIO		29
#define SIGPWR		30
#define SIGSYS		31

#define SIGCLD		SIGCHLD
#define SIGPOLL		SIGIO

typedef void (*sighandler_t)(int);

#define SIG_ERR		((void (*)(int)) -1)
#define SIG_DFL		((void (*)(int)) 0)
#define SIG_IGN		((void (*)(int)) 1)
#define SIG_HOLD	((void (*)(int)) 2)

sighandler_t signal(int signum, sighandler_t action);
int kill(int pid, int sig);
int raise(int sig);
