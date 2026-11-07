#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

#define STRING_FORMAT "%.*s"
#define STRING_ARGS(STRING) (int)(STRING).length, (STRING).data

typedef struct String8 {
    const char *data;
    size_t length;
} String8;

String8 string8_wrap(const char *data, size_t length);

String8 string8_wrap_cstring(const char *data);

#define string8_wrap_literal(literal) string8_wrap(literal, sizeof(literal))

bool string8_equal(String8 left, String8 right);

bool string8_equal_no_case(String8 left, String8 right);

size_t cstring_length(const char *data);

size_t cstring_length_up_to(const char *data, size_t max_length);

char char_lower_case(char char_);

bool char_equal_no_case(char left, char right);

bool char_is_whitespace(char char_);

bool char_is_newline(char char_);

#endif // STRING_H
