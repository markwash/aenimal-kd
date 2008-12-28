#ifndef kdtree_h
#define kdtree_h

#include <sys/types.h>

struct kdtree;
typedef struct kdtree kdtree_t;

kdtree_t *kdtree_new(size_t init_cap); 
void kdtree_free(kdtree_t *kdt);
void kdtree_internal_check(kdtree_t *kdt);

void kdtree_add(kdtree_t *kdt, double x, double y, const void *data);
const void *kdtree_get(kdtree_t *kdt, double x, double y);
int kdtree_has(kdtree_t *kdt, double x, double y);
void kdtree_del(kdtree_t *kdt, double x, double y);

size_t kdtree_size(kdtree_t *kdt);

#endif
