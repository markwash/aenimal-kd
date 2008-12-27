#ifndef kdtree_h
#define kdtree_h

#include <sys/types.h>

struct kdtree;
typedef struct kdtree kdtree_t;

kdtree_t *kdtree_new(size_t init_cap); 
void kdtree_free(kdtree_t *kdt);

#endif
