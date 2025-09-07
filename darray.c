#include "darray.h"

#include <string.h>

struct DArray {
    size_t capacity;
    size_t count;
    size_t data_frame;

    byte buffer[1];
};

static size_t _total_buffer_size(size_t capacity) {
    return sizeof(DArray) + sizeof(byte) * (capacity - 1);
}

static size_t _used_buffer_size(const DArray *self) {
    return self->data_frame * self->count;
}

static void *_allocate(size_t capacity) {
    return malloc(_total_buffer_size(capacity));
}

static size_t _grow_factor(size_t capacity) {
    if (capacity < DARRAY_MINIMUM_CAPACITY) {
        return DARRAY_MINIMUM_CAPACITY;
    }
    return capacity * DARRAY_GROWTH_CAPACITY;
}

/* Copies the data and increase the capacity to match new_capacity */
static void _grow(void *buffer, size_t new_capacity, DArrayErrorType *err) {
    buffer = realloc(buffer, _total_buffer_size(new_capacity));
}

DArray *darray_create_from_size(size_t size, size_t capacity, DArrayErrorType *err) {
    DArray *v = _allocate(capacity);

    if (v == NULL && err != NULL) {
        *err = DARRAY_ERROR_FAILED_ALLOCATION;
        return NULL;
    }

    v->capacity = capacity;
    v->count = 0;
    v->data_frame = size;

    return v;
}

DArray *darray_copy_deep(const DArray *src, DArrayErrorType *err) {
    DArray *v = _allocate(src->capacity);

    if (err != NULL && v == NULL) {
        *err = DARRAY_ERROR_FAILED_ALLOCATION;
    }

    memcpy(v, src, _total_buffer_size(src->capacity));

    return v;
}

void *darray_get(const DArray *self, size_t idx) {
    return (void *)&self->buffer[idx];
}

size_t darray_capacity(const DArray *self) {
    return self->capacity;
}

size_t darray_length(const DArray *self) {
    return self->count;
}

boolean darray_is_empty(const DArray *self) {
    return self->count == 0;
}

void darray_push(DArray *self, const void *elem, DArrayErrorType *err) {
    if (self->count + 1 >= self->capacity) {
        int new_capacity = _grow_factor(self->capacity);
        _grow(self, self->capacity * DARRAY_GROWTH_CAPACITY, err);
        self->capacity = new_capacity;
    }

    memcpy(self->buffer + self->count, elem, self->data_frame);

    self->count += 1;
}

void darray_pop(DArray *self) {
    self->count--;
}

void darray_clear(DArray *self) {
    self->count = 0;

    memset(self->buffer, 0, _used_buffer_size(self));
}

void darray_delete(DArray *self) {
    free(self);
    self = NULL;
}
