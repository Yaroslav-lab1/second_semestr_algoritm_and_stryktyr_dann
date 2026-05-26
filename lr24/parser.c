#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"

#define MAX_STACK 256

static int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

static int is_left_assoc(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/');
}

static void push_node(Node* stack[], int* top, Node* n) {
    stack[++(*top)] = n;
}
static Node* pop_node(Node* stack[], int* top) {
    return stack[(*top)--];
}
static void push_char(char stack[], int* top, char c) {
    stack[++(*top)] = c;
}
static char pop_char(char stack[], int* top) {
    return stack[(*top)--];
}
static char peek_char(char stack[], int top) {
    return stack[top];
}

Node* build_tree(const Token* tokens, int count) {
    Node* output[MAX_STACK];
    int out_top = -1;
    char op_stack[MAX_STACK];
    int op_top = -1;
    int expect_unary = 1;

    for (int i = 0; i < count; i++) {
        Token t = tokens[i];
        if (t.type == TOK_LPAREN) {
            push_char(op_stack, &op_top, '(');
            expect_unary = 1;
        }
        else if (t.type == TOK_RPAREN) {
            while (op_top >= 0 && peek_char(op_stack, op_top) != '(') {
                char op = pop_char(op_stack, &op_top);
                if (op == '~') {
                    Node* child = pop_node(output, &out_top);
                    push_node(output, &out_top, make_unary(child));
                } else {
                    Node* right = pop_node(output, &out_top);
                    Node* left = pop_node(output, &out_top);
                    push_node(output, &out_top, make_binary(op, left, right));
                }
            }
            if (op_top >= 0 && peek_char(op_stack, op_top) == '(')
                pop_char(op_stack, &op_top);
            else {
                fprintf(stderr, "Ошибка: несбалансированные скобки\n");
                return NULL;
            }
            expect_unary = 0;
        }
        else if (t.type == TOK_NUMBER || t.type == TOK_IDENT) {
            push_node(output, &out_top, make_leaf(t.str));
            expect_unary = 0;
        }
        else if (t.type == TOK_OP) {
            if (expect_unary && (t.op == '-' || t.op == '+')) {
                if (t.op == '-')
                    push_char(op_stack, &op_top, '~');
                expect_unary = 1;
                continue;
            }
            while (op_top >= 0 && peek_char(op_stack, op_top) != '(' &&
                   (precedence(peek_char(op_stack, op_top)) > precedence(t.op) ||
                   (precedence(peek_char(op_stack, op_top)) == precedence(t.op) && is_left_assoc(t.op)))) {
                char op = pop_char(op_stack, &op_top);
                if (op == '~') {
                    Node* child = pop_node(output, &out_top);
                    push_node(output, &out_top, make_unary(child));
                } else {
                    Node* right = pop_node(output, &out_top);
                    Node* left = pop_node(output, &out_top);
                    push_node(output, &out_top, make_binary(op, left, right));
                }
            }
            push_char(op_stack, &op_top, t.op);
            expect_unary = 1;
        }
    }
    while (op_top >= 0) {
        char op = pop_char(op_stack, &op_top);
        if (op == '(') {
            fprintf(stderr, "Ошибка: несбалансированные скобки\n");
            return NULL;
        }
        if (op == '~') {
            Node* child = pop_node(output, &out_top);
            push_node(output, &out_top, make_unary(child));
        } else {
            Node* right = pop_node(output, &out_top);
            Node* left = pop_node(output, &out_top);
            push_node(output, &out_top, make_binary(op, left, right));
        }
    }
    if (out_top != 0) {
        fprintf(stderr, "Ошибка разбора\n");
        return NULL;
    }
    return output[0];
}