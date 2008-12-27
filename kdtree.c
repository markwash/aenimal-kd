#include "kdtree.h"
#include "kdtree_private.h"

#include "simple_vector.h"

#include <stdlib.h>

void kdnode_init(kdnode_t *n, double x, double y, const void *data) {
	n->x = x;
	n->y = y;
	n->par = NULL;
	n->lt = NULL;
	n->gt = NULL;
	n->prev = NULL;
	n->next = NULL;
	n->data = data;
}
int kdnode_cmp(kdnode_t *n, double x, double y, int depth) {
	if (x == n->x && y == n->y) {
		return 0;
	}
	if (depth % 2 == 0) {
		return x < n->x ? -1 : 1; 
	} else {
		return y < n->y ? -1 : 1;
	}
}

struct kdtree {
	simple_vector_t *vec;
	kdnode_t *head, *tail;
	kdnode_t *root;
};

kdtree_t *kdtree_new(size_t init_cap) {

	kdtree_t *kdt;
	kdt = malloc(sizeof(kdtree_t));
	if (kdt == NULL) {
		return NULL;
	}

	if (init_cap == 0) {
		init_cap = 64;
	}
	kdt->vec = simple_vector_new(sizeof(kdnode_t), 0, init_cap);
	if (kdt->vec == NULL) {
		kdtree_free(kdt);
		return NULL;
	}

	kdt->head = NULL;
	kdt->tail = NULL;
	kdt->root = NULL;

	return kdt;
}
void kdtree_free(kdtree_t *kdt) {
	if (kdt == NULL) {
		return;
	}
	simple_vector_free(kdt->vec);
}

void kdtree_add(kdtree_t *kdt, double x, double y, const void *data) {
	
}
