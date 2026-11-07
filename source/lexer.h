#ifndef LEXER_H
#define LEXER_H

#include "array.h"
#include "string.h"
#include "token.h"

#include <stddef.h>

typedef struct Lexer {
    Array tokens;
    String8 code;
    size_t position;
    size_t line;
    size_t line_position;
} Lexer;

Lexer lexer_new(String8 code);

void lexer_free(Lexer *lexer);

Token lexer_tokenize(Lexer *lexer);

Array lexer_tokenize_all(Lexer *lexer);

String8 lexer_lexeme(const Lexer *lexer, const Token *token);

#endif // LEXER_H
