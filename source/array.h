#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef struct Array {
    void *data;
    size_t stride;
    size_t capacity;
    size_t count;
} Array;

Array array_new(size_t stride, size_t capacity);

void array_free(Array *array);

void array_resize(Array *array, size_t new_capacity);

void array_grow(Array *array);

void *array_get(Array *array, size_t index);

void *array_insert(Array *array, size_t index);

void array_remove(Array *array, size_t index, void *out);

void *array_push(Array *array);

void array_pop(Array *array, void *out);

void array_shift(Array *array, void *out);

#endif // ARRAY_H
