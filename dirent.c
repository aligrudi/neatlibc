#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct __dirent_dir {
	int fd;
	int buf_pos;
	int buf_end;
	char buf[2048];
};

DIR *opendir(char *path)
{
	DIR *dir;
	int fd;
	if ((fd = open(path, O_RDONLY | O_DIRECTORY)) < 0)
		return NULL;
	fcntl(fd, F_SETFD, fcntl(fd, F_GETFD) | FD_CLOEXEC);
	if (!(dir = malloc(sizeof(*dir)))) {
		close(fd);
		return NULL;
	}
	memset(dir, 0, sizeof(*dir));
	dir->fd = fd;
	return dir;
}

int closedir(DIR *dir)
{
	int ret;
	ret = close(dir->fd);
	free(dir);
	return ret;
}

int getdents(int fd, struct dirent *de, size_t len);

struct dirent *readdir(DIR *dir)
{
	struct dirent *de;
	int len;
	if (dir->buf_pos >= dir->buf_end) {
		len = getdents(dir->fd, (void *) dir->buf, sizeof(dir->buf));
		if (len <= 0)
			return NULL;
		dir->buf_pos = 0;
		dir->buf_end = len;
	}
	de = (void *) (dir->buf + dir->buf_pos);
	dir->buf_pos += de->d_reclen;
	return de;
}
