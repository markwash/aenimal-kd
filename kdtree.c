#include "kdtree.h"
#include "kdtree_private.h"

#include "simple_vector.h"

#include <assert.h>
#include <stdlib.h>

void kdnode_init(kdnode_t *n, double x, double y, const void *data) {
	n->x = x;
	n->y = y;
	n->par = NULL;
	n->lt = NULL;
	n->gt = NULL;
	n->prev = NULL;
	n->next = NULL;
	n->stk = NULL;
	n->depth = 0;
	n->data = data;
}
int kdnode_cmp(kdnode_t *n, double x, double y) {
	if (x == n->x && y == n->y) {
		return 0;
	}
	if (n->depth % 2 == 0) {
		return x < n->x ? -1 : 1; 
	} else {
		return y < n->y ? -1 : 1;
	}
}

void kdnode_list_pushback(kdnode_t **head, kdnode_t **tail, kdnode_t *n) {
	if (*head == NULL) {
		*head = n;
	}
	if (*tail != NULL) {
		(*tail)->next = n;
	}
	n->prev = *tail;
	*tail = n;
}
void kdnode_list_del(kdnode_t **head, kdnode_t **tail, kdnode_t *n) {

	if (*head == NULL && *tail == NULL) {
		return;
	}
	assert(*head != NULL);
	assert(*tail != NULL);

	if (n->prev != NULL) {
		n->prev->next = n->next;
	} else {
		assert(*head == n);
		(*head) = n->next;
	}

	if (n->next != NULL) {
		n->next->prev = n->prev;
	} else {
		assert(*tail == n);
		*tail = n->prev;
	}

	n->prev = NULL;
	n->next = NULL;
	
}
void kdnode_list_move(kdnode_t **head, kdnode_t **tail, kdnode_t *src, kdnode_t *dst) {
	
	if (src->prev == NULL) {
		assert(*head == src);
		*head = dst;
		dst->prev = NULL;
	} else {
		src->prev->next = dst;
		dst->prev = src->prev;
		src->prev = NULL;
	}

	if (src->next == NULL) {
		assert(*tail == src);
		*tail = dst;
		dst->next = NULL;
	} else {
		src->next->prev = dst;
		dst->next = src->next;
		src->next = NULL;
	}

}
void kdnode_list_internal_check(kdnode_t *head, kdnode_t *tail, kdnode_t *n) {
	if (n->prev == NULL) {
		assert(head == n);
	} else {
		assert(n->prev->next == n);
	}
	if (n->next == NULL) {
		assert(tail == n);
	} else {
		assert(n->next->prev == n);
	}
}

void kdnode_tree_insert(kdnode_t **root, kdnode_t *n) {
	
	if (*root == NULL) {
		*root = n;
		n->depth = 0;
		return;
	}
	
	kdnode_t *parent, *cur = *root;
	int cmp;
	while (cur != NULL) {
		parent = cur;
		cmp = kdnode_cmp(cur, n->x, n->y);
		if (cmp < 0) {
			cur = cur->lt;
		} else {
			cur = cur->gt;
		}
	}
		
	n->par = parent;
	n->depth = parent->depth + 1;
	if (cmp < 0) {
		parent->lt = n;
	} else {
		parent->gt = n;
	}
}
kdnode_t *kdnode_tree_search(kdnode_t *root, double x, double y) {
	kdnode_t *cur = root;
	int cmp;
	while (cur != NULL) {
		cmp = kdnode_cmp(cur, x, y);
		if (cmp == 0) {
			return cur;
		} else if (cmp < 0) {
			cur = cur->lt;
		} else {
			cur = cur->gt;
		}
	}
	return NULL;
}
void kdnode_tree_del(kdnode_t **root, kdnode_t *n) {

	// break off from parent, including root
	if (n->par == NULL) {
		assert(*root == n);
		*root = NULL;
	} else {
		if (n->par->lt == n) {
			n->par->lt = NULL;
		} else {
			assert(n->par->gt == n);
			n->par->gt = NULL;
		}
		n->par = NULL;
	}

	// break off children, initializing the reinsert stack
	kdnode_t *stk = NULL;
	if (n->lt != NULL) {
		kdnode_stack_push(&stk, n->lt);
		n->lt->par = NULL;
		n->lt = NULL;
	}
	if (n->gt != NULL) {
		kdnode_stack_push(&stk, n->gt);
		n->gt->par = NULL;
		n->gt = NULL;
	}

	// reinsert all the orphans
	kdnode_t *k;
	while (1) {
		k = kdnode_stack_pop(&stk);
		if (k == NULL) {
			break;
		}
		if (k->lt != NULL) {
			kdnode_stack_push(&stk, k->lt);
			k->lt->par = NULL;
			k->lt = NULL;
		}
		if (k->gt != NULL) {
			kdnode_stack_push(&stk, k->gt);
			k->gt->par = NULL;
			k->gt = NULL;
		}
		kdnode_tree_insert(root, k);
	}
	
}
void kdnode_tree_move(kdnode_t **root, kdnode_t *src, kdnode_t *dst) {
	
	// repair parent/root
	if (src->par == NULL) {
		assert(*root == src);
		*root = dst;
		dst->par = NULL;
	} else {
		if (src->par->lt == src) {
			src->par->lt = dst;
			dst->par = src->par;
			src->par = NULL;
		} else {
			assert(src->par->gt == src);
			src->par->gt = dst;
			dst->par = src->par;
			src->par = NULL;
		}
	}

	// repair children
	dst->lt = src->lt;
	src->lt = NULL;
	if (dst->lt != NULL) {
		dst->lt->par = dst;
	}
	dst->gt = src->gt;
	src->gt = NULL;
	if (dst->gt != NULL) {
		dst->gt->par = dst;
	}

	// copy depth
	dst->depth = src->depth;

}
void kdnode_tree_internal_check(kdnode_t *root, kdnode_t *n) {
	if (n->par == NULL) {
		assert(root == n);
		assert(n->depth == 0);
	} else {
		assert(n->par->lt == n || n->par->gt == n);
		assert(n->depth == n->par->depth + 1); 
	}
	if (n->lt != NULL) {
		assert(n->lt->par == n);
	}
	if (n->gt != NULL) {
		assert(n->gt->par == n);
	}
}

void kdnode_stack_push(kdnode_t **stk, kdnode_t *n) {
	n->stk = *stk;
	*stk = n;
}
kdnode_t *kdnode_stack_pop(kdnode_t **stk) {
	if (*stk == NULL) {
		return NULL;
	}
	kdnode_t *n;
	n = *stk;
	*stk = n->stk;
	n->stk = NULL;
	return n;
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
void kdtree_internal_check(kdtree_t *kdt) {
	size_t i;
	kdnode_t *n;
	for (i = 0; i < simple_vector_size(kdt->vec); i++) {
		n = (kdnode_t *)simple_vector_get_ref(kdt->vec, i);
		kdnode_list_internal_check(kdt->head, kdt->tail, n);
		kdnode_tree_internal_check(kdt->root, n);
	}
}

void kdtree_add(kdtree_t *kdt, double x, double y, const void *data) {
	
	// allocate and initialize the node
	simple_vector_grow(kdt->vec, 1);
	kdnode_t *n = (kdnode_t *) simple_vector_last_ref(kdt->vec);
	kdnode_init(n, x, y, data);

	// put the node at the back of the list
	kdnode_list_pushback(&kdt->head, &kdt->tail, n);

	// insert the node into the tree
	kdnode_tree_insert(&kdt->root, n);

}
const void *kdtree_get(kdtree_t *kdt, double x, double y) {
	kdnode_t *n = kdnode_tree_search(kdt->root, x, y);
	if (n == NULL) {
		return NULL;
	}
	return n->data;
}
int kdtree_has(kdtree_t *kdt, double x, double y) {
	if (kdnode_tree_search(kdt->root, x, y) == NULL) {
		return 0;
	} else {
		return 1;
	}
}
void kdtree_del(kdtree_t *kdt, double x, double y) {

	// find the node if it exists
	kdnode_t *n = kdnode_tree_search(kdt->root, x, y);
	if (n == NULL) {
		return;
	}

	// remove it from the list
	kdnode_list_del(&kdt->head, &kdt->tail, n);

	// remove it from the tree
	kdnode_tree_del(&kdt->root, n);

	// remove it from the vector
	kdnode_t *last;
	last = simple_vector_last_ref(kdt->vec);
	if (last != n) {
		kdnode_init(n, last->x, last->y, last->data);
		kdnode_list_move(&kdt->head, &kdt->tail, last, n);
		kdnode_tree_move(&kdt->root, last, n);
	}
	simple_vector_shrink(kdt->vec, 1);
	
}

size_t kdtree_size(kdtree_t *kdt) {
	return simple_vector_size(kdt->vec);
}

struct kdtree_iter_ctx {
	kdnode_t node;
};

kdtree_iter_ctx_t *kdtree_iter_ctx_new(kdtree_t *kdt) {
	return (kdtree_iter_ctx_t *) kdt->head;
}
void kdtree_iter_ctx_free(kdtree_iter_ctx_t *ctx) {
	return;
}
void kdtree_iter_ctx_next(kdtree_iter_ctx_t **ctx, double *x, double *y, const void **data) {
	kdnode_t *n;
	n = (kdnode_t *) *ctx;
	if (n == NULL) {
		return;
	}
	*x = n->x;
	*y = n->y;
	*data = n->data;
	*ctx = (kdtree_iter_ctx_t *) n->next;
}

static double euclid_metric(double xdel, double ydel) {
	return xdel * xdel + ydel * ydel;
}

void kdtree_nn(kdtree_t *kdt, double x, double y, neighbor_t *nb, metric_fn mfn) {
	
	assert(kdt->root != NULL);
	kdnode_t *cur = kdt->root;
	kdnode_t *stk = NULL;
	double dist;

	nb->dist = -1.0;

	while ( 1 ) {

		if (cur != NULL) {
			kdnode_stack_push(&stk, cur);
			if (kdnode_cmp(cur, x, y) < 0) {
				cur = cur->lt;
			} else {
				cur = cur->gt;
			}
		} else {
			cur = kdnode_stack_pop(&stk);
			if (cur == NULL) {
				return;
			}
			if (mfn == NULL) {
				dist = euclid_metric(x - cur->x, y - cur->y);
			} else {
				dist = mfn(x - cur->x, y - cur->y);
			}
			if (nb->dist == -1.0 || dist < nb->dist) {
				nb->dist = dist;
				nb->x = cur->x;
				nb->y = cur->y;
				nb->data = cur->data;
			}
	
			// consider distance to dividing line
			if (cur->depth % 2 == 0) {
				if (mfn == NULL) {
					dist = euclid_metric(x - cur->x, 0);
				} else {
					dist = mfn(x - cur->x, 0);
				}  
			} else {
				if (mfn == NULL) {
					dist = euclid_metric(0, y - cur->y);
				} else {
					dist = mfn(0, y - cur->y);
				}
			}

			// if the distance is less than best so far,
			// then there can exist points beyond the line
			// that are closer than the current best, so
			// pursue that subtree
			if (dist < nb->dist) {
				if (kdnode_cmp(cur, x, y) < 0) {
					cur = cur->gt;
				} else {
					cur = cur->lt;
				}
			} else {
				cur = NULL;
			}

		}
	}
}
