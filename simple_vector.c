#include "simple_vector.h"

#include <assert.h>
#include <stdlib.h>

struct sub_vector;
typedef struct sub_vector sub_vector_t;
struct sub_vector {
	size_t start;
	size_t len;
	sub_vector_t *next;
	char data[];
};

struct simple_vector {
	size_t elem_sz;
	size_t sz;
	size_t cap;
	sub_vector_t *subs;
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
	sv->subs = malloc(sizeof(sub_vector_t) + sv->cap * sv->elem_sz);
	if (sv->subs == NULL) {
		simple_vector_free(sv);
		return NULL;
	}
	sv->subs->start = 0;
	sv->subs->len = sv->cap;
	sv->subs->next = NULL;
	return sv;
}
void simple_vector_free(simple_vector_t *sv) {
	if (sv == NULL) {
		return;
	}
	sub_vector_t *tmp;
	while (sv->subs != NULL) {
		tmp = sv->subs->next;
		free(sv->subs);
		sv->subs = tmp;
	}
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
	sub_vector_t *subvec;
	for (subvec = sv->subs; which < subvec->start; subvec = subvec->next);
	assert(which < subvec->start + subvec->len);
	memcpy(
		subvec->data + sv->elem_sz * (which - subvec->start),
		data,
		sv->elem_sz
		);

}
void simple_vector_get(simple_vector_t *sv, size_t which, void *data_r) {

	assert(which < sv->sz);
	sub_vector_t *subvec;
	for (subvec = sv->subs; which < subvec->start; subvec = subvec->next);
	assert(which < subvec->start + subvec->len);
	memcpy(
		data_r,
		subvec->data + sv->elem_sz * (which - subvec->start),
		sv->elem_sz
		);

}
void *simple_vector_get_ref(simple_vector_t *sv, size_t which) {
	assert(which < sv->sz);
	sub_vector_t *subvec;
	for (subvec = sv->subs; which < subvec->start; subvec = subvec->next);
	assert(which < subvec->start + subvec->len);
	return subvec->data + sv->elem_sz * (which - subvec->start);
}

void simple_vector_recap(simple_vector_t *sv, size_t cap) {

	if (cap <= sv->cap) {
		return;
	}
	sub_vector_t *subvec;
	for (
		subvec = sv->subs; 
		subvec->next != NULL; 
		subvec = subvec->next
		);
	subvec->next = malloc(sizeof(sub_vector_t) + sv->elem_sz * (cap - sv->cap));
	assert(subvec->next != NULL);
	subvec->next->start = sv->cap;
	subvec->next->len = cap - sv->cap;
	subvec->next->next = NULL;
	sv->cap = cap;

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
void *simple_vector_last_ref(simple_vector_t *sv) {

	return simple_vector_get_ref(sv, sv->sz - 1);

}
