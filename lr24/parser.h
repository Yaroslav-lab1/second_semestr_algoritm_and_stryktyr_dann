#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "tokenizer.h"

Node* build_tree(const Token* tokens, int count);

#endif