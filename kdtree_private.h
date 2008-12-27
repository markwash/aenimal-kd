#ifndef kdtree_private_h
#define kdtree_private_h

struct kdnode;
typedef struct kdnode kdnode_t;

struct kdnode {
	double x, y;
	kdnode_t *par;
	kdnode_t *lt, *gt;
	kdnode_t *prev, *next;
	const void *data;
};

void kdnode_init(kdnode_t *n, double x, double y, const void *data);
int kdnode_cmp(kdnode_t *n, double x, double y, int depth);

#endif
