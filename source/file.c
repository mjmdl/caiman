#include "file.h"
#include "memory.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define PRINT_WITH_ERRNO_REASON(...) \
    do { \
        int err = errno; \
        fprintf(stderr, "Error: " __VA_ARGS__); \
        if (err != 0) { \
            fprintf(stderr, " because %s", strerror(err)); \
        } \
        fprintf(stderr, ".\n"); \
    } while (0)


bool file_read(String8 file_path, String8 *out_data)
{
    assert(file_path.data != NULL);
    assert(out_data != NULL);
    assert(out_data->data == NULL);

    errno = 0;
    FILE *file = fopen(file_path.data, "rb");
    if (file == NULL) {
        PRINT_WITH_ERRNO_REASON("Failed to open file "STRING_FORMAT, STRING_ARGS(file_path));
        return false;
    }

    errno = 0;
    long length = 0;
    if (fseek(file, 0, SEEK_END) < 0 ||
        (length = ftell(file)) < 0 ||
        fseek(file, 0, SEEK_SET) < 0)
    {
        PRINT_WITH_ERRNO_REASON("Failed to get size of file "STRING_FORMAT, STRING_ARGS(file_path));
        fclose(file);
        return false;
    }

    size_t size = length + 1;
    char *data = memory_new(size);

    errno = 0;
    size_t bytes_read = fread(data, 1, length, file);
    if (bytes_read != (size_t)length) {
        PRINT_WITH_ERRNO_REASON("Failed to read %ld bytes out of file "STRING_FORMAT, length, STRING_ARGS(file_path));
        memory_free(data);
        fclose(file);
        return false;
    }
    data[length] = '\0';

    fclose(file);
    *out_data = string8_wrap(data, length);
    return true;
}

void file_free(String8 *file)
{
    assert(file != NULL);
    assert(file->data != NULL);

    memory_free((void *)file->data);
}
