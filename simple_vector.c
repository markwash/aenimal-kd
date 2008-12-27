#include "simple_vector.h"

#include <assert.h>
#include <stdlib.h>

struct simple_vector {
	size_t elem_sz;
	size_t sz;
	size_t cap;
	void *data;
};

simple_vector_t *simple_vector_new(size_t elem_sz, size_t sz, size_t cap) {
	simple_vector_t *sv;
	sv = malloc(sizeof(simple_vector_t));
	if (sv == NULL) {
		return sv;
	}
	sv->elem_sz = elem_sz;
	sv->sz = sz;
	sv->cap = cap >= sz ? cap : sz;
	sv->data = calloc(sv->cap, sv->elem_sz);
	if (sv->data == NULL) {
		simple_vector_free(sv);
		return NULL;
	}
	return sv;
}
void simple_vector_free(simple_vector_t *sv) {
	if (sv == NULL) {
		return;
	}
	free(sv->data);
	free(sv);
	return;
}

size_t simple_vector_size(simple_vector_t *sv) {
	return sv->sz;
}
size_t simple_vector_cap(simple_vector_t *sv) {
	return sv->cap;
}

void simple_vector_set(simple_vector_t *sv, size_t which, void *data) {

	assert(which < sv->sz);
	memcpy(sv->data + sv->elem_sz * which, data, sv->elem_sz);

}
void simple_vector_get(simple_vector_t *sv, size_t which, void *data_r) {

	assert(which < sv->sz);
	memcpy(data_r, sv->data + sv->elem_sz * which, sv->elem_sz);

}

void simple_vector_recap(simple_vector_t *sv, size_t cap) {

	void *tmp = realloc(sv->data, cap * sv->elem_sz);
	assert(tmp != NULL);
	sv->data = tmp;
	sv->cap = cap;
	if (sv->sz > cap) {
		sv->sz = cap;
	}

}
void simple_vector_resize(simple_vector_t *sv, size_t sz) {

	if (sz > 2 * sv->cap) {
		simple_vector_recap(sv, sz);
	} else if (sz > sv->cap) {
		simple_vector_recap(sv, 2 * sv->cap);
	}
	sv->sz = sz;
	
}
void simple_vector_grow(simple_vector_t *sv, size_t sz) {
	simple_vector_resize(sv, sv->sz + sz);
}
void simple_vector_shrink(simple_vector_t *sv, size_t sz) {
	if (sz > sv->sz) {
		simple_vector_resize(sv, 0);
		return;
	} 
	simple_vector_resize(sv, sv->sz - sz);
}

void simple_vector_pushback(simple_vector_t *sv, void *data) {

	simple_vector_grow(sv, 1);
	simple_vector_set(sv, sv->sz - 1, data);

}
void simple_vector_last(simple_vector_t *sv, void *data_r) {

	simple_vector_get(sv, sv->sz - 1, data_r);

}
