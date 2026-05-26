#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum { TOK_NUMBER, TOK_IDENT, TOK_OP, TOK_LPAREN, TOK_RPAREN } TokenType;

typedef struct {
    TokenType type;
    char op;
    char* str;
} Token;

Token* tokenize(const char* expr, int* count);
void free_tokens(Token* tokens, int count);

#endif