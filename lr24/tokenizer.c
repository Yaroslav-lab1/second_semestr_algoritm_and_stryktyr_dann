#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

#define INIT_CAP 32

static void add_token(Token** tokens, int* count, int* cap, TokenType type, char op, const char* str) {
    if (*count >= *cap) {
        *cap *= 2;
        *tokens = realloc(*tokens, (*cap) * sizeof(Token));
    }
    Token t;
    t.type = type;
    t.op = op;
    t.str = str ? strdup(str) : NULL;
    (*tokens)[(*count)++] = t;
}

Token* tokenize(const char* expr, int* count) {
    int cap = INIT_CAP;
    Token* tokens = malloc(cap * sizeof(Token));
    *count = 0;

    while (*expr) {
        if (isspace(*expr)) { expr++; continue; }
        if (isdigit(*expr) || (*expr == '.' && isdigit(*(expr+1)))) {
            const char* start = expr;
            while (isdigit(*expr)) expr++;
            if (*expr == '.') {
                expr++;
                while (isdigit(*expr)) expr++;
            }
            int len = expr - start;
            char* num = (char*)malloc(len+1);
            strncpy(num, start, len);
            num[len] = '\0';
            add_token(&tokens, count, &cap, TOK_NUMBER, 0, num);
            free(num);
        }
        else if (isalpha(*expr) || *expr == '_') {
            const char* start = expr;
            while (isalnum(*expr) || *expr == '_') expr++;
            int len = expr - start;
            char* id = (char*)malloc(len+1);
            strncpy(id, start, len);
            id[len] = '\0';
            add_token(&tokens, count, &cap, TOK_IDENT, 0, id);
            free(id);
        }
        else if (*expr == '+' || *expr == '-' || *expr == '*' || *expr == '/') {
            add_token(&tokens, count, &cap, TOK_OP, *expr, NULL);
            expr++;
        }
        else if (*expr == '(') {
            add_token(&tokens, count, &cap, TOK_LPAREN, 0, NULL);
            expr++;
        }
        else if (*expr == ')') {
            add_token(&tokens, count, &cap, TOK_RPAREN, 0, NULL);
            expr++;
        }
        else {
            fprintf(stderr, "Неизвестный символ: %c\n", *expr);
            free_tokens(tokens, *count);
            return NULL;
        }
    }
    return tokens;
}

void free_tokens(Token* tokens, int count) {
    for (int i = 0; i < count; i++)
        free(tokens[i].str);
    free(tokens);
}