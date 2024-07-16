#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define PGSIZE		4096
#define PGMASK		(PGSIZE - 1)
#define MSETMAX		4096
#define MSETLEN		(1 << 15)

/* placed at the beginning of regions for small allocations */
struct mset {
	int refs;	/* number of allocations */
	int size;	/* remaining size */
};

/* placed before each small allocation */
struct mhdr {
	int moff;	/* mset offset */
	int size;	/* allocation size */
};

static struct mset *pool;
static struct mset *pool1;	/* a freed pool */

static int mk_pool(void)
{
	if ((pool == NULL || pool->refs > 0) && pool1 != NULL) {
		pool = pool1;
		pool1 = NULL;
	}
	if (pool != NULL && pool->refs == 0) {
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
	if (!pool || pool->size + n + sizeof(struct mhdr) > MSETLEN)
		if (mk_pool())
			return NULL;
	m = (void *) pool + pool->size;
	((struct mhdr *) m)->moff = pool->size;
	((struct mhdr *) m)->size = n;
	pool->refs++;
	pool->size += (n + sizeof(struct mhdr) + 7) & ~7;
	if (!((unsigned long) (pool + pool->size + sizeof(struct mhdr)) & PGMASK))
		pool->size += sizeof(long);
	return m + sizeof(struct mhdr);
}

void free(void *v)
{
	if (!v)
		return;
	if ((unsigned long) v & PGMASK) {
		struct mhdr *mhdr = v - sizeof(struct mhdr);
		struct mset *mset = (void *) mhdr - mhdr->moff;
		mset->refs--;
		if (mset->refs == 0 && mset != pool) {
			if (pool1 != NULL)
				munmap(mset, MSETLEN);
			else
				pool1 = mset;
		}
	} else {
		munmap(v - PGSIZE, *(long *) (v - PGSIZE));
	}
}

void *calloc(long n, long sz)
{
	void *r = malloc(n * sz);
	if (r)
		memset(r, 0, n * sz);
	return r;
}

static long msize(void *v)
{
	if ((unsigned long) v & PGMASK)
		return ((struct mhdr *) (v - sizeof(*v)))->size;
	return *(long *) (v - PGSIZE);
}

void *realloc(void *v, long sz)
{
	void *r = malloc(sz);
	if (r && v) {
		memcpy(r, v, msize(v));
		free(v);
	}
	return r;
}
