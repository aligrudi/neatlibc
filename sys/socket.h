#include <sys/types.h>

#define SHUT_RD		0
#define SHUT_WR		1
#define SHUT_RDWR	2

#define SOCK_STREAM	1
#define SOCK_DGRAM	2

#define SOCK_RAW	3

#define SOCK_CLOEXEC   02000000
#define SOCK_NONBLOCK  04000

#define PF_UNSPEC       0
#define PF_LOCAL        1
#define PF_UNIX         PF_LOCAL
#define PF_INET         2

#define AF_UNSPEC       PF_UNSPEC
#define AF_LOCAL        PF_LOCAL
#define AF_UNIX         AF_LOCAL
#define AF_INET         PF_INET

typedef unsigned short sa_family_t;
typedef unsigned socklen_t;

struct sockaddr {
	sa_family_t sa_family;
	char sa_data[14];
};

int socket(int domain, int type, int protocol);

int shutdown(int socket, int how);

int bind(int socket, struct sockaddr *addr, socklen_t addr_len);
int connect(int socket, struct sockaddr *addr, socklen_t addr_len);
int listen(int socket, int backlog);
int accept(int socket, struct sockaddr *addr, socklen_t *addr_len);

int getsockname(int socket, struct sockaddr *addr, socklen_t *addr_len);
int getpeername(int socket, struct sockaddr *addr, socklen_t *addr_len);

ssize_t send(int socket, void *buf, size_t len, int flags);
ssize_t recv(int socket, void *buf, size_t len, int flags);
ssize_t sendto(int socket, void *msg, size_t len, int flags, struct sockaddr *addr, socklen_t addr_len);
ssize_t recvfrom(int socket, void *msg, size_t len, int flags, struct sockaddr *addr, socklen_t *addr_len);

int getsockopt(int socket, int level, int name, void *value, socklen_t *len);
int setsockopt(int socket, int level, int name, void *value, socklen_t len);
