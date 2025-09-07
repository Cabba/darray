#include <stdio.h>

#include "darray.h"

#define ASSERT_EQ(LEFT, RIGHT)                                          \
    if (LEFT != RIGHT) {                                                \
        printf("error @ line %i: %s != %s\n", __LINE__, #LEFT, #RIGHT); \
        exit(-1);                                                       \
    }

#define ASSERT_NEQ(LEFT, RIGHT)                                         \
    if (LEFT == RIGHT) {                                                \
        printf("error @ line %i: %s == %s\n", __LINE__, #LEFT, #RIGHT); \
        exit(-1);                                                       \
    }

#define ASSERT(EXP)                                               \
    if (!EXP) {                                                   \
        printf("error @ line %i: %s == false\n", __LINE__, #EXP); \
        exit(-1);                                                 \
    }

#define DBG(EXP) \
    printf("%s = %d\n", #EXP, EXP);

typedef struct Point {
    int x;
    int y;
} Point;

int main(int argc, char **argv) {
    {
        DArray *v;
        Point p, *p_stored;
        p.x = 10;
        p.y = 11;

        v = darray_create_from_size(sizeof(Point), 1, NULL);

        ASSERT_EQ(darray_capacity(v), 1);
        ASSERT_EQ(darray_length(v), 0);
        ASSERT(darray_is_empty(v));

        darray_push(v, &p, NULL);

        ASSERT_EQ(darray_capacity(v), DARRAY_MINIMUM_CAPACITY);
        ASSERT_EQ(darray_length(v), 1);
        ASSERT(!darray_is_empty(v));

        p_stored = darray_get(v, 0);

        ASSERT_EQ(p_stored->x, 10);
        ASSERT_EQ(p_stored->y, 11);

        darray_push(v, &p, NULL);

        ASSERT_EQ(darray_capacity(v), DARRAY_MINIMUM_CAPACITY);
        ASSERT_EQ(darray_length(v), 2);
        ASSERT(!darray_is_empty(v));

        darray_clear(v);
        ASSERT_EQ(darray_capacity(v), DARRAY_MINIMUM_CAPACITY);
        ASSERT_EQ(darray_length(v), 0);
        ASSERT(darray_is_empty(v));

        darray_delete(v);
        ASSERT_EQ(v, NULL);
    }

    printf("all tests passed\n");

    return 0;
}
