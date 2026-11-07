#include "token.h"

#define _(LITERAL) \
    {.data = (LITERAL), .length = sizeof(LITERAL) - 1}

typedef struct Keyword_Lexeme {
    const Token_Kind kind;
    const String8 lexeme;
} Keyword_Lexeme;

static const Keyword_Lexeme keyword_lexemes[] = {
    {TOKEN_IMPORT, _("import")},
    {TOKEN_EXPORT, _("export")},
    {TOKEN_FOREIGN, _("foreign")},
    {TOKEN_FN, _("fn")},
    {TOKEN_STRUCT, _("struct")},
    {TOKEN_UNION, _("union")},
    {TOKEN_ENUM, _("enum")},
    {TOKEN_IF, _("if")},
    {TOKEN_THEN, _("then")},
    {TOKEN_ELSE, _("else")},
    {TOKEN_CASE, _("case")},
    {TOKEN_FOR, _("for")},
    {TOKEN_CONTINUE, _("continue")},
    {TOKEN_BREAK, _("break")},
    {TOKEN_RETURN, _("return")},
    {TOKEN_CATCH, _("catch")},
    {TOKEN_AND, _("and")},
    {TOKEN_OR, _("or")},
    {TOKEN_NOT, _("not")},
    {TOKEN_MUT, _("mut")},
    {TOKEN_CONST, _("const")},
    {TOKEN_TRUE, _("true")},
    {TOKEN_FALSE, _("false")},
    {TOKEN_NIL, _("nil")}};

#undef _

Token_Kind token_kind_match_keywords(String8 lexeme)
{
    size_t count = sizeof(keyword_lexemes) / sizeof(keyword_lexemes)[0];
    for (size_t i = 0; i < count; i += 1) {
        Keyword_Lexeme keyword = keyword_lexemes[i];
        if (string8_equal(lexeme, keyword.lexeme)) {
            return keyword.kind;
        }
    }
    return TOKEN_UNKNOWN;
}

String8 token_kind_name(Token_Kind kind)
{
    #define CASE(KIND) \
        case TOKEN_##KIND: \
            return string8_wrap_literal(#KIND)
    switch (kind) {
    CASE(UNKNOWN);
    CASE(END_OF_INPUT);

    CASE(IDENTIFIER);
    CASE(NUMBER);
    CASE(STRING);
    CASE(STRING_TEMPLATE);
    CASE(ANNOTATION);

    CASE(IMPORT);
    CASE(EXPORT);
    CASE(FOREIGN);
    CASE(FN);
    CASE(STRUCT);
    CASE(UNION);
    CASE(ENUM);
    CASE(IF);
    CASE(THEN);
    CASE(ELSE);
    CASE(CASE);
    CASE(FOR);
    CASE(CONTINUE);
    CASE(BREAK);
    CASE(RETURN);
    CASE(CATCH);
    CASE(AND);
    CASE(OR);
    CASE(NOT);
    CASE(MUT);
    CASE(CONST);
    CASE(TRUE);
    CASE(FALSE);
    CASE(NIL);

    CASE(PARENTHESIS_LEFT);
    CASE(PARENTHESIS_RIGHT);
    CASE(CURLY_BRACE_LEFT);
    CASE(CURLY_BRACE_RIGHT);
    CASE(SQUARE_BRACKET_LEFT);
    CASE(SQUARE_BRACKET_RIGHT);
    CASE(DOT);
    CASE(DOT_AMPERSAND);
    CASE(DOT_STAR);
    CASE(COMMA);
    CASE(SEMICOLON);
    CASE(COLON);
    CASE(EQUAL);
    CASE(EQUAL_EQUAL);
    CASE(LESS);
    CASE(LESS_EQUAL);
    CASE(DIAMOND);
    CASE(GREATER);
    CASE(GREATER_EQUAL);
    CASE(PLUS);
    CASE(PLUS_EQUAL);
    CASE(MINUS);
    CASE(MINUS_EQUAL);
    CASE(ARROW);
    CASE(STAR);
    CASE(STAR_EQUAL);
    CASE(SLASH);
    CASE(SLASH_EQUAL);
    CASE(PERCENT);
    CASE(PERCENT_EQUAL);
    CASE(PIPE);
    CASE(PIPE_EQUAL);
    CASE(AMPERSAND);
    CASE(AMPERSAND_EQUAL);
    CASE(CARET);
    CASE(CARET_EQUAL);
    CASE(TILDE);
    CASE(TILDE_EQUAL);
    default:
        return string8_wrap_literal("*invalid Token_Kind value*");
    }
    #undef CASE
}

#undef _
