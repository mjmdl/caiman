#ifndef TOKEN_H
#define TOKEN_H

#include "string.h"

typedef enum Token_Kind {
    TOKEN_UNKNOWN = 0,
    TOKEN_END_OF_INPUT,

    TOKEN_IDENTIFIER,           // Literal: /[a-zA-Z_][a-zA-Z0-9_]*/
    TOKEN_NUMBER,               // Literal: /(0[xX][0-9a-fA-F]+|0[bB][01]+|[0-9]+(\.[0-9]*)?([eE][+-]?[0-9]+)?)/
    TOKEN_STRING,               // Literal: /"([^"\\]|\\.)*"/
    TOKEN_STRING_TEMPLATE,      // Literal: /\$"([^"\\]|\\.|{{|}})*"/
    TOKEN_ANNOTATION,           // Literal: ///[^\n]*

    TOKEN_IMPORT,               // Keyword: `import`
    TOKEN_EXPORT,               // Keyword: `export`
    TOKEN_FOREIGN,              // Keyword: `foreign`
    TOKEN_FN,                   // Keyword: `fn`
    TOKEN_STRUCT,               // Keyword: `struct`
    TOKEN_UNION,                // Keyword: `union`
    TOKEN_ENUM,                 // Keyword: `enum`
    TOKEN_IF,                   // Keyword: `if`
    TOKEN_THEN,                 // Keyword: `then`
    TOKEN_ELSE,                 // Keyword: `else`
    TOKEN_CASE,                 // Keyword: `case`
    TOKEN_FOR,                  // Keyword: `for`
    TOKEN_CONTINUE,             // Keyword: `continue`
    TOKEN_BREAK,                // Keyword: `break`
    TOKEN_RETURN,               // Keyword: `return`
    TOKEN_CATCH,                // Keyword: `catch`
    TOKEN_AND,                  // Keyword: `and`
    TOKEN_OR,                   // Keyword: `or`
    TOKEN_NOT,                  // Keyword: `not`
    TOKEN_MUT,                  // Keyword: `mut`
    TOKEN_CONST,                // Keyword: `const`
    TOKEN_TRUE,                 // Keyword: `true`
    TOKEN_FALSE,                // Keyword: `false`
    TOKEN_NIL,                  // Keyword: `nil`

    TOKEN_PARENTHESIS_LEFT,     // Punctuation: `(`
    TOKEN_PARENTHESIS_RIGHT,    // Punctuation: `)`
    TOKEN_CURLY_BRACE_LEFT,     // Punctuation: `{`
    TOKEN_CURLY_BRACE_RIGHT,    // Punctuation: `}`
    TOKEN_SQUARE_BRACKET_LEFT,  // Punctuation: `[`
    TOKEN_SQUARE_BRACKET_RIGHT, // Punctuation: `]`
    TOKEN_DOT,                  // Punctuation: `.`
    TOKEN_DOT_AMPERSAND,        // Punctuation: `.&`
    TOKEN_DOT_STAR,             // Punctuation: `.*`
    TOKEN_COMMA,                // Punctuation: `,`
    TOKEN_SEMICOLON,            // Punctuation: `;`
    TOKEN_COLON,                // Punctuation: `:`
    TOKEN_EQUAL,                // Punctuation: `=`
    TOKEN_EQUAL_EQUAL,          // Punctuation: `==`
    TOKEN_LESS,                 // Punctuation: `<`
    TOKEN_LESS_EQUAL,           // Punctuation: `<=`
    TOKEN_DIAMOND,              // Punctuation: `<>`
    TOKEN_GREATER,              // Punctuation: `>`
    TOKEN_GREATER_EQUAL,        // Punctuation: `>=`
    TOKEN_PLUS,                 // Punctuation: `+`
    TOKEN_PLUS_EQUAL,           // Punctuation: `+=
    TOKEN_MINUS,                // Punctuation: `-`
    TOKEN_MINUS_EQUAL,          // Punctuation: `-=`
    TOKEN_ARROW,                // Punctuation: `->`
    TOKEN_STAR,                 // Punctuation: `*`
    TOKEN_STAR_EQUAL,           // Punctuation: `*=`
    TOKEN_SLASH,                // Punctuation: `/`
    TOKEN_SLASH_EQUAL,          // Punctuation: `/=`
    TOKEN_PERCENT,              // Punctuation: `%`
    TOKEN_PERCENT_EQUAL,        // Punctuation: `%=`
    TOKEN_PIPE,                 // Punctuation: `|`
    TOKEN_PIPE_EQUAL,           // Punctuation: `|=`
    TOKEN_AMPERSAND,            // Punctuation: `&`
    TOKEN_AMPERSAND_EQUAL,      // Punctuation: `&=`
    TOKEN_CARET,                // Punctuation: `^`
    TOKEN_CARET_EQUAL,          // Punctuation: `^=`
    TOKEN_TILDE,                // Punctuation: `~`
    TOKEN_TILDE_EQUAL,          // Punctuation: `~=`
    TOKEN_DOLLAR,               // Punctuation: `$`

    ENUM_TOKEN_KIND_COUNT,
} Token_Kind;

typedef struct Token {
    Token_Kind kind;
    size_t position;
    size_t line;
    size_t column;
    size_t length;
} Token;

Token_Kind token_kind_match_keywords(String8 lexeme);

Token_Kind token_kind_match_punctuations(String8 lexeme, size_t *out_length);

String8 token_kind_name(Token_Kind kind);

#endif // TOKEN_H
