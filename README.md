# darray

A simple, type-generic dynamic array (vector) implementation in ANSI C that automatically manages its own memory.

It is a very simple implementation in ANSI C of an API similar to C++ `std::vector`.

## Quick Start
Just copy `vector.h` and `vector.c` inside your project and use it.

## Core API

- `darray_create(TYPE, CAPACITY, ERROR)`: Creates a new dynamic array.
- `darray_delete(DArray *self)`: Frees all memory used by the array.
- `darray_push(DArray *self, const void *elem, &err)`: Appends an element to the end.
- `darray_pop(DArray *self)`: Removes the last element.
- `darray_get(const DArray *self, size_t idx)`: Returns a pointer to the element at idx.
- `darray_length(const DArray *self)`: Returns the number of elements.
- `darray_capacity(const DArray *self)`: Returns the current allocated capacity.
- `darray_clear(DArray *self)`: Removes all elements, setting length to 0.


## Example

```c
#include <stdio.h>
#include "darray.h"

int main() {
    // Create an array to hold integers
    DArray *arr = darray_create(int, 5, NULL);
    if (!arr) return 1;

    // Push 10 values into the array
    for (int i = 0; i < 10; ++i) {
        darray_push(arr, &i, NULL);
    }

    // Print the contents
    printf("Array (Length: %zu, Capacity: %zu): ", darray_length(arr), darray_capacity(arr));
    for (size_t i = 0; i < darray_length(arr); ++i) {
        printf("%d ", *(int*)darray_get(arr, i));
    }
    printf("\n");

    // Clean up
    darray_delete(arr);
    return 0;
}
```

# Testing
```
make
./test
```


