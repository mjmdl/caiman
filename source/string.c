#include "string.h"

#include <assert.h>
#include <limits.h>
#include <stdint.h>

String8 string8_wrap(const char *data, size_t length)
{
    assert((data == NULL) == (length == 0));

    String8 string = {
        .data = data,
        .length = length};
    return string;
}

String8 string8_wrap_cstring(const char *data)
{
    return string8_wrap(data, cstring_length(data));
}

bool string8_equal(String8 left, String8 right)
{
    if (left.length != right.length) {
        return false;
    }
    if (left.data == right.data) {
        return true;
    }
    if (left.data == NULL) {
        return false;
    }
    if (right.data == NULL) {
        return false;
    }

    const uint8_t *this = (const uint8_t *)left.data;
    const uint8_t *that = (const uint8_t *)right.data;

    for (size_t i = 0; i < left.length; i += 1) {
        if (this[i] != that[i]) {
            return false;
        }
    }

    return true;
}

bool string8_equal_no_case(String8 left, String8 right)
{
    if (left.length != right.length) {
        return false;
    }
    if (left.data == right.data) {
        return true;
    }
    if (left.data == NULL) {
        return false;
    }
    if (right.data == NULL) {
        return false;
    }

    const uint8_t *this = (const uint8_t *)left.data;
    const uint8_t *that = (const uint8_t *)right.data;

    for (size_t i = 0; i < left.length; i += 1) {
        if (char_equal_no_case(this[i], that[i])) {
            return false;
        }
    }

    return true;
}

size_t cstring_length(const char *data)
{
    return cstring_length_up_to(data, UINT_MAX);
}

size_t cstring_length_up_to(const char *data, size_t max_length)
{
    assert(max_length > 0);

    size_t length = 0;
    while (data[length] != '\0' && length < max_length) {
        length += 1;
    }
    return length;
}

char char_lower_case(char char_)
{
    if (char_ < 'A' || char_ > 'Z') {
        return char_;
    }

    char offset = 'a' - 'A';
    char result = char_ + offset;
    return result;
}

bool char_equal_no_case(char left, char right)
{
    return char_lower_case(left) == char_lower_case(right);
}

bool char_is_whitespace(char char_)
{
    // FIXME: CRLF?
    return char_ == ' ' || char_ == '\n' || char_ == '\0';
}

bool char_is_newline(char char_)
{
    // FIXME: CRLF?
    return char_ == '\n';
}
