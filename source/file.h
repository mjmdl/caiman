#ifndef FILE_H
#define FILE_H

#include "string.h"

#include <stddef.h>

bool file_read(String8 file_path, String8 *out_data);

void file_free(String8 *file);

#endif // FILE_H
