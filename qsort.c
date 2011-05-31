/* based on musl libc's qsort.c */
#include <stdlib.h>
#include <string.h>

#define MIN(a, b)	((a) < (b) ? (a) : (b))

static void swap(char *a, char *b, int sz)
{
	char tmp[256];
	while (sz) {
		int l = MIN(sizeof(tmp), sz);
		memcpy(tmp, a, l);
		memcpy(a, b, l);
		memcpy(b, tmp, l);
		a += l;
		b += l;
		sz -= l;
	}
}

static void fix(char *a, int root, int n, int sz, int (*cmp)(void *, void *))
{
	while (2 * root <= n) {
		int max = 2 * root;
		if (max < n && cmp(a + max * sz, a + (max + 1) * sz) < 0)
			max++;
		if (max && cmp(a + root * sz, a + max * sz) < 0) {
			swap(a + root * sz, a + max * sz, sz);
			root = max;
		} else {
			break;
		}
	}
}

void qsort(void *a, int n, int sz, int (*cmp)(void *, void *))
{
	int i;

	if (!n)
		return;
	for (i = (n + 1) >> 1; i; i--)
		fix(a, i - 1, n - 1, sz, cmp);
	for (i = n - 1; i; i--) {
		swap(a, a + i * sz, sz);
		fix(a, 0, i - 1, sz, cmp);
	}
}
