#ifndef simple_vector_h
#define simple_vector_h

struct simple_vector;

typedef struct simple_vector simple_vector_t;

simple_vector_t *simple_vector_new();
void simple_vector_free(simple_vector_t *sv);

#endif
