#include "array.h"
#include "memory.h"

#include <assert.h>

#define ARRAY_GROW_TIMES (2)
#define ARRAY_DEFAULT_CAPACITY (2)

Array array_new(size_t stride, size_t capacity)
{
    assert(stride > 0);
    assert(capacity > 0);

    size_t size = stride * capacity;
    void *data = memory_new(size);
    
    Array array = {
        .data = data,
        .stride = stride,
        .capacity = capacity,
        .count = 0};
    return array;
}

void array_free(Array *array)
{
    assert(array != NULL);
    assert(array->data != NULL);

    memory_free(array->data);
}

void array_resize(Array *array, size_t new_capacity)
{
    assert(array != NULL);
    assert(new_capacity > 0);
    assert((array->data == NULL) == (array->capacity == 0));

    if (array->capacity == new_capacity) {
        return;
    }

    array->data = memory_resize(array->data, new_capacity);
    array->capacity = new_capacity;
    if (array->count > new_capacity) {
        array->count = new_capacity;
    }
}

void array_grow(Array *array)
{
    assert(array != NULL);
    assert((array->data == NULL) == (array->capacity == 0));
    assert(array->capacity <= (SIZE_MAX / ARRAY_GROW_TIMES));

    size_t new_capacity;
    if (array->capacity > 0) {
        new_capacity = (array->capacity * ARRAY_GROW_TIMES);
    } else {
        new_capacity = ARRAY_DEFAULT_CAPACITY;
    }

    array_resize(array, new_capacity);
}

void *array_get(Array *array, size_t index)
{
    assert(array != NULL);
    assert(array->data != NULL);
    assert(index < array->count);

    size_t offset = index * array->stride;
    void *result = (uint8_t *)array->data + offset;
    return result;
}

void *array_insert(Array *array, size_t index)
{
    assert(array != NULL);
    assert(index <= array->count);
    assert((array->data == NULL) == (array->capacity == 0));

    if (array->count == array->capacity) {
        array_grow(array);
    }

    size_t offset = index * array->stride;
    uint8_t *slot = (uint8_t *)array->data + offset;

    if (index != array->count) {
        uint8_t *from = slot;
        uint8_t *into = slot + array->stride;
        size_t slots_ahead = array->count - index;
        size_t bytes_ahead = slots_ahead * array->stride;

        memory_copy(from, into, bytes_ahead);
        memory_zero(slot, array->stride);
    }

    array->count += 1;
    return slot;
}

void array_remove(Array *array, size_t index, void *out)
{
    assert(array != NULL);
    assert(index < array->count);
    assert(array->data != NULL);

    size_t offset = index * array->stride;
    uint8_t *slot = (uint8_t *)array->data + offset;

    if (out != NULL) {
        memory_copy(slot, out, array->stride);
    }

    if (index != (array->count - 1)) {
        uint8_t *into = slot;
        uint8_t *from = slot + array->stride;
        size_t slots_ahead = array->count - index - 1;
        size_t bytes_ahead = slots_ahead * array->stride;

        memory_copy(from, into, bytes_ahead);
    }

    memory_zero(slot, array->stride);
    array->count -= 1;
}

void *array_push(Array *array)
{
    assert(array != NULL);

    void *result = array_insert(array, array->count);
    return result;
}

void array_pop(Array *array, void *out)
{
    assert(array != NULL);

    size_t index = array->count - 1;
    array_remove(array, index, out);
}

void array_shift(Array *array, void *out)
{
    assert(array != NULL);

    array_remove(array, 0, out);
}
