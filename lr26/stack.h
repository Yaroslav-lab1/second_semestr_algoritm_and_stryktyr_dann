#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

typedef struct {
    const Stack *stack;
    int current;
} StackIterator;

void stack_init(Stack *s);
void stack_destroy(Stack *s);
bool stack_is_empty(const Stack *s);
bool stack_is_full(const Stack *s);
bool stack_push(Stack *s, int value);
bool stack_pop(Stack *s, int *out_value);
bool stack_peek(const Stack *s, int *out_value);
int stack_size(const Stack *s);
StackIterator stack_iterator_begin(const Stack *s);
bool stack_iterator_has_next(const StackIterator *it);
bool stack_iterator_next(StackIterator *it, int *out_value);

#endif