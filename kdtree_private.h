#ifndef kdtree_private_h
#define kdtree_private_h

struct kdnode;
typedef struct kdnode kdnode_t;

struct kdnode {
	double x, y;
	kdnode_t *par;
	kdnode_t *lt, *gt;
	kdnode_t *prev, *next;
	kdnode_t *stk;
	const void *data;
};

void kdnode_init(kdnode_t *n, double x, double y, const void *data);
int kdnode_cmp(kdnode_t *n, double x, double y, int depth);

void kdnode_list_pushback(kdnode_t **head, kdnode_t **tail, kdnode_t *n);
void kdnode_list_del(kdnode_t **head, kdnode_t **tail, kdnode_t *n);
void kdnode_list_move(kdnode_t **head, kdnode_t **tail, kdnode_t *src, kdnode_t *dst);

void kdnode_tree_insert(kdnode_t **root, kdnode_t *n);
kdnode_t *kdnode_tree_search(kdnode_t *root, double x, double y);
void kdnode_tree_del(kdnode_t **root, kdnode_t *n);
void kdnode_tree_move(kdnode_t **root, kdnode_t *src, kdnode_t *dst);

void kdnode_stack_push(kdnode_t **stk, kdnode_t *n);
kdnode_t *kdnode_stack_pop(kdnode_t **stk);

#endif
