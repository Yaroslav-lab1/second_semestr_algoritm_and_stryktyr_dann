#include <stdio.h>
#include "printer.h"

static int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

static void print_infix_rec(const Node* node, int parent_prec) {
    if (!node) return;
    if (node->type == NODE_LEAF) {
        printf("%s", node->data.value);
    }
    else if (node->type == NODE_UNARY_MINUS) {
        printf("-");
        if (node->data.unary.child->type != NODE_LEAF) {
            printf("(");
            print_infix_rec(node->data.unary.child, 999);
            printf(")");
        } else {
            print_infix_rec(node->data.unary.child, 999);
        }
    }
    else if (node->type == NODE_BINARY) {
        int prec = precedence(node->data.bin.op);
        int left_prec = (node->data.bin.left->type == NODE_BINARY) ?
                         precedence(node->data.bin.left->data.bin.op) : 999;
        int right_prec = (node->data.bin.right->type == NODE_BINARY) ?
                          precedence(node->data.bin.right->data.bin.op) : 999;
        if (left_prec < prec) {
            printf("(");
            print_infix_rec(node->data.bin.left, prec);
            printf(")");
        } else {
            print_infix_rec(node->data.bin.left, prec);
        }
        printf(" %c ", node->data.bin.op);
        if (right_prec < prec || (right_prec == prec && (node->data.bin.op == '-' || node->data.bin.op == '/'))) {
            printf("(");
            print_infix_rec(node->data.bin.right, prec);
            printf(")");
        } else {
            print_infix_rec(node->data.bin.right, prec);
        }
    }
}

void print_infix(const Node* node) {
    print_infix_rec(node, 0);
}

void println_infix(const Node* node) {
    print_infix(node);
    printf("\n");
}

void print_tree_vertical(const Node* node, int indent) {
    if (!node) return;
    if (node->type == NODE_LEAF) {
        printf("%*sLeaf(%s)\n", indent*2, "", node->data.value);
    } else if (node->type == NODE_UNARY_MINUS) {
        printf("%*sUnaryMinus\n", indent*2, "");
        print_tree_vertical(node->data.unary.child, indent+1);
    } else if (node->type == NODE_BINARY) {
        printf("%*sOp(%c)\n", indent*2, "", node->data.bin.op);
        print_tree_vertical(node->data.bin.left, indent+1);
        print_tree_vertical(node->data.bin.right, indent+1);
    }
}