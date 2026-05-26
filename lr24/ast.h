#ifndef AST_H
#define AST_H

typedef enum { NODE_LEAF, NODE_UNARY_MINUS, NODE_BINARY } NodeType;

typedef struct Node {
    NodeType type;
    union {
        char* value;
        struct { struct Node* child; } unary;
        struct { char op; struct Node* left, *right; } bin;
    } data;
} Node;

Node* make_leaf(const char* value);
Node* make_unary(Node* child);
Node* make_binary(char op, Node* left, Node* right);
void free_tree(Node* node);

#endif