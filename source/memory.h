#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

void *memory_new(size_t size);

void memory_free(void *memory);

void *memory_resize(void *memory, size_t new_size);

void memory_fill_bytes(void *memory, size_t size, uint8_t byte_value);

void memory_zero(void *memory, size_t size);

void memory_copy(const void *from_memory, void *into_memory, size_t size);

#endif // MEMORY_H
