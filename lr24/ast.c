#include <stdlib.h>
#include <string.h>
#include "ast.h"

Node* make_leaf(const char* value) {
    Node* n = malloc(sizeof(Node));
    n->type = NODE_LEAF;
    n->data.value = strdup(value);
    return n;
}

Node* make_unary(Node* child) {
    Node* n = malloc(sizeof(Node));
    n->type = NODE_UNARY_MINUS;
    n->data.unary.child = child;
    return n;
}

Node* make_binary(char op, Node* left, Node* right) {
    Node* n = malloc(sizeof(Node));
    n->type = NODE_BINARY;
    n->data.bin.op = op;
    n->data.bin.left = left;
    n->data.bin.right = right;
    return n;
}

void free_tree(Node* node) {
    if (!node) return;
    if (node->type == NODE_LEAF)
        free(node->data.value);
    else if (node->type == NODE_UNARY_MINUS)
        free_tree(node->data.unary.child);
    else if (node->type == NODE_BINARY) {
        free_tree(node->data.bin.left);
        free_tree(node->data.bin.right);
    }
    free(node);
}