#ifndef simple_vector_h
#define simple_vector_h

#include "sys/types.h"

struct simple_vector;

typedef struct simple_vector simple_vector_t;

simple_vector_t *simple_vector_new(
		size_t elem_sz,
		size_t sz,
		size_t cap
);
void simple_vector_free(simple_vector_t *sv);

size_t simple_vector_size(simple_vector_t *sv);
size_t simple_vector_cap(simple_vector_t *sv);

void simple_vector_set(simple_vector_t *sv, size_t which, void *data);
void simple_vector_get(simple_vector_t *sv, size_t which, void *data_r);
void *simple_vector_get_ref(simple_vector_t *sv, size_t which);
//TODO: currently these refs aren't persistent across calls to recap

void simple_vector_recap(simple_vector_t *sv, size_t cap);
void simple_vector_resize(simple_vector_t *sv, size_t sz);
void simple_vector_grow(simple_vector_t *sv, size_t sz);
void simple_vector_shrink(simple_vector_t *sv, size_t sz);

void simple_vector_pushback(simple_vector_t *sv, void *data);
void simple_vector_last(simple_vector_t *sv, void *data_r);

#endif
