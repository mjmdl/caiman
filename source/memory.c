#include "memory.h"

#include <assert.h>
#include <stdlib.h>

void *memory_new(size_t size)
{
    assert(size > 0);

    void *result = malloc(size);
    if (result == NULL) {
        abort();
    }
    return result;
}

void memory_free(void *memory)
{
    assert(memory != NULL);

    free(memory);
}

void *memory_resize(void *memory, size_t new_size)
{
    assert(new_size > 0);

    void *result = realloc(memory, new_size);
    if (result == NULL) {
        abort();
    }
    return result;
}

void memory_fill_bytes(void *memory, size_t size, uint8_t byte_value)
{
    assert(memory != NULL);
    assert(size > 0);

    uint8_t *into = memory;
    for (size_t i = 0; i < size; i += 1) {
        into[i] = byte_value;
    }
}

void memory_zero(void *memory, size_t size)
{
    memory_fill_bytes(memory, size, 0);
}

void memory_copy(const void *from_memory, void *into_memory, size_t size)
{
    assert(from_memory != NULL);
    assert(into_memory != NULL);
    assert(size > 0);

    const uint8_t *from = from_memory;
    uint8_t *into = into_memory;
    for (size_t i = 0; i < size; i += 1) {
        into[i] = from[i];
    }
}
