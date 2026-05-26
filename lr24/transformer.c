#include <stddef.h>
#include "transformer.h"
#include "ast.h"

Node* replace_subtraction(Node* node) {
    if (!node) return NULL;
    if (node->type == NODE_LEAF)
        return node;
    if (node->type == NODE_UNARY_MINUS) {
        node->data.unary.child = replace_subtraction(node->data.unary.child);
        return node;
    }
    if (node->type == NODE_BINARY) {
        node->data.bin.left = replace_subtraction(node->data.bin.left);
        node->data.bin.right = replace_subtraction(node->data.bin.right);
        if (node->data.bin.op == '-') {
            node->data.bin.op = '+';
            Node* unary = make_unary(node->data.bin.right);
            node->data.bin.right = unary;
        }
        return node;
    }
    return node;
}