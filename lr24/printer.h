#ifndef PRINTER_H
#define PRINTER_H

#include "ast.h"

void print_tree_vertical(const Node* node, int indent);
void print_infix(const Node* node);
void println_infix(const Node* node);

#endif