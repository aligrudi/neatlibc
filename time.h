struct timespec {
	long tv_sec;
	long tv_nsec;
};

int nanosleep(struct timespec *req, struct timespec *rem);
