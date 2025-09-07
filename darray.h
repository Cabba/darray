#ifndef DARRAY_H
#define DARRAY_H

#include <stddef.h>
#include <stdlib.h>

#define DARRAY_GROWTH_CAPACITY 1.5
#define DARRAY_MINIMUM_CAPACITY 8

typedef unsigned int uint;
typedef unsigned char byte;
typedef uint boolean;

typedef enum { DARRAY_ERROR_FAILED_ALLOCATION } DArrayErrorType;

typedef struct DArray DArray;

DArray *darray_create_from_size(size_t size, size_t capacity, DArrayErrorType *err);

#define darray_create(TYPE, CAPACITY, ERROR) \
    darray_create_from_size(sizeof(TYPE), CAPACITY, ERROR);

void darray_delete(DArray *self);

/** Perform a deep copy of a target darray. Deep copy means that all the
 * internal memory of the darray will be copyed. */
DArray *darray_copy_deep(const DArray *target, DArrayErrorType *err);

void darray_push(DArray *self, const void *elem, DArrayErrorType *err);
void darray_pop(DArray *self);
void *darray_get(const DArray *self, size_t idx);
size_t darray_capacity(const DArray *self);
size_t darray_length(const DArray *self);
boolean darray_is_empty(const DArray *self);
void darray_clear(DArray *self);

#endif
