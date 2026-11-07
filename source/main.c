#include "file.h"
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    const char *program_name = argv[0];
    if (argc != 2) {
        fprintf(stderr, "Usage: %s code.cai\n", program_name);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    String8 code = {0};
    if (!file_read(string8_wrap_cstring(file_path), &code)) {
        return EXIT_FAILURE;
    }

    Lexer lexer = lexer_new(code);
    lexer_tokenize_all(&lexer);

    for (size_t i = 0; i < lexer.tokens.count; i += 1) {
        const Token *token = array_get(&lexer.tokens, i);
        String8 lexeme = lexer_lexeme(&lexer, token);
        String8 kind_name = token_kind_name(token->kind);
        printf(
            "%zu:%zu(%zu) #%zu: "STRING_FORMAT" `"STRING_FORMAT"`\n",
            token->position,
            token->column,
            token->length,
            i,
            STRING_ARGS(kind_name),
            STRING_ARGS(lexeme));
    }

    lexer_free(&lexer);
    file_free(&code);
    return EXIT_SUCCESS;
}
