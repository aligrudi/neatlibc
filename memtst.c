#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MTHASH(v)		((((long) v) >> 8) & 0xffff)
#define MEMTSTSZ		(1 << 18)
#define MTHASHSZ		(1 << 16)
#define MTBTLEN			5

struct memtst {
	long *mem;
	long n;
	long bt[MTBTLEN];
	int freed;
};

static struct memtst *memtst;	/* memtst records */
static int memtst_n;		/* number of items in memtst[] */
static int memtst_sz = MEMTSTSZ;
static int *memtst_tail;	/* hash table list tails */
static int *memtst_prev;	/* hash table list previous items */
static int memtst_mcnt, memtst_fcnt;	/* malloc() and free() count */
static long memtst_mmax;	/* maximum memory used */
static long memtst_mcur;	/* allocated memory */
static long memtst_mtot;	/* total memory allocated */

static int memtst_full(void)
{
	return memtst_n == memtst_sz;
}

static char *memtst_show(long *bt)
{
	static char s[100];
	snprintf(s, sizeof(s), "%8p %8p %8p %8p %8p",
		bt[0], bt[1], bt[2], bt[3], bt[4]);
	return s;
}

static void memtst_summary(void)
{
	int i;
	fprintf(stderr, "memtst %d %d  %ld", memtst_mcnt, memtst_fcnt, memtst_mtot);
	if (memtst_full()) {
		fprintf(stderr, "\nmemtst: increase MEMTSTSZ\n");
		return;
	}
	fprintf(stderr, " %ld\n", memtst_mmax);
	for (i = 0; i < memtst_n; i++) {
		struct memtst *mt = &memtst[i];
		if (!mt->freed)
			fprintf(stderr, "memtstleak %8p %8ld %s\n",
				mt->mem, mt->n, memtst_show(mt->bt));
	}
}

static void memtst_init(void)
{
	memtst = malloc(memtst_sz * sizeof(memtst[0]));
	memtst_prev = malloc(memtst_sz * sizeof(memtst_prev[0]));
	memtst_tail = malloc(MTHASHSZ * sizeof(memtst_tail[0]));
	memset(memtst_tail, 0xff, MTHASHSZ * sizeof(memtst_tail[0]));
	atexit(memtst_summary);
}

static void memtst_put(void *mem, int n, long *bt)
{
	struct memtst *mt;
	if (!memtst)
		memtst_init();
	if (memtst_full())
		return;
	mt = &memtst[memtst_n];
	mt->mem = mem;
	mt->n = n;
	memcpy(mt->bt, bt, sizeof(mt->bt));
	memtst_prev[memtst_n] = memtst_tail[MTHASH(mem)];
	memtst_tail[MTHASH(mem)] = memtst_n;
	memtst_n++;
}

static struct memtst *memtst_get(void *mem)
{
	int idx;
	if (!memtst)
		return NULL;
	idx = memtst_tail[MTHASH(mem)];
	while (idx >= 0) {
		struct memtst *mt = &memtst[idx];
		if (!mt->freed && mt->mem == mem)
			return mt;
		idx = memtst_prev[idx];
	}
	return NULL;
}

long memtst_back(int n);

static void memtst_bt(long *bt)
{
	bt[0] = memtst_back(1);
	bt[1] = memtst_back(2);
	bt[2] = memtst_back(3);
	bt[3] = memtst_back(4);
	bt[4] = memtst_back(5);
}

void *memtst_malloc(long n)
{
	void *v = malloc(n);
	long bt[MTBTLEN];
	memtst_bt(bt);
	if (!v)
		fprintf(stderr, "memtstfail %8ld %s\n", n, memtst_show(bt));
	else
		memtst_put(v, n, bt);
	if (v) {
		memtst_mcnt++;
		memtst_mcur += n;
		memtst_mtot += n;
	}
	if (memtst_mcur > memtst_mmax)
		memtst_mmax = memtst_mcur;
	return v;
}

void memtst_free(void *v)
{
	struct memtst *mt;
	if (!v)
		return;
	memtst_fcnt++;
	mt = memtst_get(v);
	if (!mt && !memtst_full()) {
		long bt[MTBTLEN];
		memtst_bt(bt);
		fprintf(stderr, "memtstfree %8p %s\n", v, memtst_show(bt));
		return;
	}
	if (mt)
		memtst_mcur -= mt->n;
	if (mt)
		mt->freed = 1;
	free(v);
}

void *memtst_calloc(long n, long sz)
{
	void *r = memtst_malloc(n * sz);
	if (r)
		memset(r, 0, n * sz);
	return r;
}

void *memtst_realloc(void *v, long sz)
{
	void *r = memtst_malloc(sz);
	if (r) {
		long sz = *(long *) (v - sizeof(long));
		memcpy(r, v, sz);
		memtst_free(v);
	}
	return r;
}
