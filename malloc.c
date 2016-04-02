#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define PGSIZE		4096
#define PGMASK		(PGSIZE - 1)
#define MSETMAX		4096
#define MSETLEN		(1 << 15)

struct mset {
	int refs;
	int size;
};

static struct mset *pool;

static int mk_pool(void)
{
	if (pool && !pool->refs) {
		pool->size = sizeof(*pool);
		return 0;
	}
	pool = mmap(NULL, MSETLEN, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (pool == MAP_FAILED) {
		pool = NULL;
		return 1;
	}
	pool->size = sizeof(*pool);
	pool->refs = 0;
	return 0;
}

void *malloc(long n)
{
	void *m;
	if (n >= MSETMAX) {
		m = mmap(NULL, n + PGSIZE, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (m == MAP_FAILED)
			return NULL;
		*(long *) m = n + PGSIZE;	/* store length in the first page */
		return m + PGSIZE;
	}
	if (!pool || MSETLEN - pool->size < n + sizeof(void *))
		if (mk_pool())
			return NULL;
	m = (void *) pool + pool->size;
	*(void **) m = pool;			/* the address of the owning mset */
	pool->refs++;
	pool->size += (n + sizeof(void *) + 7) & ~7;
	if (!((unsigned long) (pool + pool->size + sizeof(void *)) & PGMASK))
		pool->size += sizeof(long);
	return m + sizeof(void *);
}

void *calloc(long n, long sz)
{
	void *r = malloc(n * sz);
	if (r)
		memset(r, 0, n * sz);
	return r;
}

void free(void *v)
{
	if (!v)
		return;
	if ((unsigned long) v & PGMASK) {
		struct mset *mset = *(void **) (v - sizeof(void *));
		mset->refs--;
		if (!mset->refs && mset != pool)
			munmap(mset, mset->size);
	} else {
		munmap(v - PGSIZE, *(long *) (v - PGSIZE));
	}
}
