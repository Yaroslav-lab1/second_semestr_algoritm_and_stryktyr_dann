#include "stack.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 4

void stack_init(Stack *s) {
    s->data = (int*) malloc(INITIAL_CAPACITY * sizeof(int));
    s->top = -1;
    s->capacity = INITIAL_CAPACITY;
}

void stack_destroy(Stack *s) {
    free(s->data);
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}

bool stack_is_empty(const Stack *s) {
    return s->top == -1;
}

bool stack_is_full(const Stack *s) {
    return s->top + 1 >= s->capacity;
}

static bool stack_resize(Stack *s) {
    int new_capacity = s->capacity * 2;
    int *new_data = (int*) realloc(s->data, new_capacity * sizeof(int));
    if (!new_data) return false;
    s->data = new_data;
    s->capacity = new_capacity;
    return true;
}

bool stack_push(Stack *s, int value) {
    if (stack_is_full(s) && !stack_resize(s)) {
        return false;
    }
    s->data[++(s->top)] = value;
    return true;
}

bool stack_pop(Stack *s, int *out_value) {
    if (stack_is_empty(s)) return false;
    *out_value = s->data[(s->top)--];
    return true;
}

bool stack_peek(const Stack *s, int *out_value) {
    if (stack_is_empty(s)) return false;
    *out_value = s->data[s->top];
    return true;
}

int stack_size(const Stack *s) {
    return s->top + 1;
}

StackIterator stack_iterator_begin(const Stack *s) {
    StackIterator it;
    it.stack = s;
    it.current = 0;
    return it;
}

bool stack_iterator_has_next(const StackIterator *it) {
    return it->current <= it->stack->top;
}

bool stack_iterator_next(StackIterator *it, int *out_value) {
    if (!stack_iterator_has_next(it)) return false;
    *out_value = it->stack->data[it->current];
    it->current++;
    return true;
}