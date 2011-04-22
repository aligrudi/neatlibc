#define WNOHANG		0x00000001
#define WUNTRACED	0x00000002

int wait(int *status);
int waitpid(int pid, int *status, int options);
