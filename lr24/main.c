#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"
#include "transformer.h"
#include "printer.h"

void process(const char* expr) {
    printf("========================================\n");
    printf("Исходное выражение: %s\n\n", expr);

    int n;
    Token* tokens = tokenize(expr, &n);
    if (!tokens) return;

    Node* tree = build_tree(tokens, n);
    free_tokens(tokens, n);
    if (!tree) return;

    printf("Исходное дерево:\n");
    print_tree_vertical(tree, 0);

    Node* transformed = replace_subtraction(tree);
    printf("\nПреобразованное дерево:\n");
    print_tree_vertical(transformed, 0);

    printf("\nТекстовый вид: ");
    println_infix(transformed);

    free_tree(transformed);
    printf("\n");
}

int main() {
    process("a + b * c");
    process("a - b * c");
    process("a - b - c");
    process("(a - b) * (c - d)");
    process("-x - y");
    process("123 - 456");
    return 0;
}