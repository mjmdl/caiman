#include "lexer.h"

#define TOKENS_INITIAL_CAPACITY (1024)

static bool lexer_inbounds(const Lexer *lexer)
{
    return lexer->position < lexer->code.length;
}

static bool lexer_inbounds_by(const Lexer *lexer, ptrdiff_t offset)
{
    return (lexer->position + offset) < lexer->code.length;
}

static char lexer_peek(const Lexer *lexer)
{
    return lexer->code.data[lexer->position];
}

static char lexer_peek_by(const Lexer *lexer, ptrdiff_t offset)
{
    return lexer->code.data[lexer->position + offset];
}

static void lexer_advance(Lexer *lexer)
{
    lexer->position += 1;
}

static void lexer_advance_by(Lexer *lexer, ptrdiff_t offset)
{
    lexer->position += offset;
}

static bool lexer_newline(Lexer *lexer)
{
    if (!char_is_newline(lexer_peek(lexer))) {
        return false;
    }

    lexer->position += 1;
    lexer->line += 1;
    lexer->line_position = lexer->position;
    return true;
}

static Token *lexer_make_token(Lexer *lexer, Token_Kind kind)
{
    Token *token = array_push(&lexer->tokens);
    *token = (Token) {
        .kind = kind,
        .position = lexer->position,
        .line = lexer->line,
        .column = lexer->position - lexer->line_position,
        .length = 1};
    return token;
}

static bool lexer_skip_whitespaces(Lexer *lexer)
{
    bool skipped = false;
    while (lexer_inbounds(lexer) && char_is_whitespace(lexer_peek(lexer))) {
        if (!lexer_newline(lexer)) {
            lexer_advance(lexer);
        }
        skipped = true;
    }
    return skipped;
}

static bool lexer_can_start_comment(const Lexer *lexer)
{
    return
        lexer_peek(lexer) == '/' &&
        lexer_inbounds_by(lexer, 1);
}

static bool lexer_skip_single_line_comment(Lexer *lexer)
{
    if (!lexer_can_start_comment(lexer)) {
        return false;
    }
    if (lexer_peek_by(lexer, 1) != '/') {
        return false;
    }

    if (lexer_inbounds_by(lexer, 2) && lexer_peek_by(lexer, 2) == '/') {
        return false;
    }
    lexer_advance_by(lexer, 2);

    while (lexer_inbounds(lexer) && !char_is_newline(lexer_peek(lexer))) {
        if (lexer_peek(lexer) == '\\') {
            size_t by = lexer_inbounds_by(lexer, 1) ? 2 : 1;
            lexer_advance_by(lexer, by);
            continue;
        }

        lexer_advance(lexer);
    }

    if (lexer_inbounds(lexer)) {
        lexer_newline(lexer);
    }
    return true;
}

static bool lexer_skip_block_comment(Lexer *lexer)
{
    if (!lexer_can_start_comment(lexer)) {
        return false;
    }
    if (lexer_peek_by(lexer, 1) != '*') {
        return false;
    }
    
    lexer_advance_by(lexer, 2);
    int openings = 1;

    while (lexer_inbounds(lexer) && openings > 0) {
        if (lexer_peek(lexer) == '\\') {
            int by = lexer_inbounds_by(lexer, 1) ? 2 : 1;
            lexer_advance_by(lexer, by);
            continue;
        }

        if (lexer_peek(lexer) == '/') {
            lexer_advance(lexer);
            if (lexer_inbounds(lexer) && lexer_peek(lexer) == '*') {
                openings += 1;
                lexer_advance(lexer);
            }
            continue;
        }

        if (lexer_peek(lexer) == '*') {
            lexer_advance(lexer);
            if (lexer_inbounds(lexer) && lexer_peek(lexer) == '/') {
                openings -= 1;
                lexer_advance(lexer);
            }
            continue;
        }

        lexer_advance(lexer);
    }
    return true;
}

static bool lexer_skip_no_ops(Lexer *lexer)
{
    // FIXME: Ugly code.
    bool skipped = false;
    while (true) {
        bool break_ = true;
        if (lexer_skip_whitespaces(lexer)) {
            break_ = false;
        }
        if (lexer_skip_single_line_comment(lexer)) {
            break_ = false;
        }
        if (lexer_skip_block_comment(lexer)) {
            break_ = false;
        }
        if (break_) {
            break;
        }
        skipped = true;
    }
    return skipped;
}

static bool lexer_tokenize_identifier(Lexer *lexer, Token **out_token)
{
    if (!char_can_begin_identifier(lexer_peek(lexer))) {
        return false;
    }

    Token *token = lexer_make_token(lexer, TOKEN_IDENTIFIER);
    lexer_advance(lexer);

    while (lexer_inbounds(lexer) && char_can_continue_identifier(lexer_peek(lexer))) {
        lexer_advance(lexer);
    }
    token->length = lexer->position - token->position;

    *out_token = token;
    return true;
}

static bool lexer_tokenize_names(Lexer *lexer, Token **out_token)
{
    Token *token = NULL;
    if (!lexer_tokenize_identifier(lexer, &token)) {
        return false;
    }

    Token_Kind keyword = token_kind_match_keywords(lexer_lexeme(lexer, token));
    if (keyword != TOKEN_UNKNOWN) {
        token->kind = keyword;
    }

    *out_token = token;
    return true;
}

static bool lexer_tokenize_annotation(Lexer *lexer, Token **out_token)
{
    (void)lexer;
    (void)out_token;
    return false;
}

static bool lexer_tokenize_number(Lexer *lexer, Token **out_token)
{
    (void)lexer;
    (void)out_token;
    return false;
}

static bool lexer_tokenize_string(Lexer *lexer, Token **out_token)
{
    (void)lexer;
    (void)out_token;
    return false;
}

static bool lexer_tokenize_punctuation(Lexer *lexer, Token **out_token)
{
    (void)lexer;
    (void)out_token;
    return false;
}

Lexer lexer_new(String8 code)
{
    assert(code.data != NULL && code.length > 0);

    Array tokens = array_new(sizeof(Token), TOKENS_INITIAL_CAPACITY);

    Lexer lexer = {
        .tokens = tokens,
        .code = code,
        .position = 0,
        .line = 1,
        .line_position = 0};
    return lexer;
}

void lexer_free(Lexer *lexer)
{
    assert(lexer != NULL);

    array_free(&lexer->tokens);
}

Token lexer_tokenize(Lexer *lexer)
{
    assert(lexer != NULL);

    lexer_skip_no_ops(lexer);

    Token *token = NULL;
    if (lexer_tokenize_names(lexer, &token) ||
        lexer_tokenize_annotation(lexer, &token) ||
        lexer_tokenize_string(lexer, &token) ||
        lexer_tokenize_number(lexer, &token) ||
        lexer_tokenize_punctuation(lexer, &token))
    {
        return *token;
    }

    token = lexer_make_token(lexer, TOKEN_UNKNOWN);
    lexer_advance(lexer);
    return *token;
}

Array lexer_tokenize_all(Lexer *lexer)
{
    assert(lexer != NULL);

    while (lexer_inbounds(lexer)) {
        lexer_tokenize(lexer);
    }
    return lexer->tokens;
}

String8 lexer_lexeme(const Lexer *lexer, const Token *token)
{
    const char *data = lexer->code.data + token->position;
    String8 result = string8_wrap(data, token->length);
    return result;
}
