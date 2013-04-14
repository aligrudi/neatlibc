#include <stdlib.h>
#include <sys/mman.h>

#define MSET_SIZE		(1 << 15)
#define MMAP_MIN		(1 << 12)

struct mset {
	int refs;
	int size;
};

struct mem {
	int size;
	struct mset *mset;
};

static struct mset *pool;

static void mk_pool(void)
{
	if (pool && !pool->refs) {
		pool->size = sizeof(*pool);
		return;
	}
	pool = mmap(NULL, MSET_SIZE, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (pool == MAP_FAILED) {
		pool = NULL;
		return;
	}
	pool->size = sizeof(*pool);
	pool->refs = 0;
}

void *malloc(long n)
{
	struct mem *mem;
	n += sizeof(*mem);
	if (n >= MMAP_MIN) {
		mem = mmap(NULL, n, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (mem == MAP_FAILED)
			return NULL;
		mem->size = n;
		mem->mset = NULL;
		return (void *) mem + sizeof(*mem);
	}
	if (!pool || MSET_SIZE - pool->size < n)
		mk_pool();
	if (!pool)
		return NULL;
	mem = (void *) pool + pool->size;
	mem->mset = pool;
	mem->size = n;
	pool->refs++;
	pool->size += (n + 7) & ~7;
	return (void *) mem + sizeof(*mem);
}

void free(void *v)
{
	struct mem *mem = v - sizeof(struct mem);
	if (!v)
		return;
	if (mem->mset) {
		struct mset *mset = mem->mset;
		mset->refs--;
		if (!mset->refs && mset != pool)
			munmap(mset, mset->size);
	} else {
		munmap(mem, mem->size);
	}
}
