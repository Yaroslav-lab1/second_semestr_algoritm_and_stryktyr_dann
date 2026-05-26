#include "stack_sort.h"
#include <stdlib.h>

void stack_merge_sort(Stack *s);

static void split_stack(Stack *src, Stack *left, Stack *right) {
    int size = stack_size(src);
    int half = size / 2;

    StackIterator it = stack_iterator_begin(src);
    int value;
    for (int i = 0; i < half; i++) {
        stack_iterator_next(&it, &value);
        stack_push(left, value);
    }
    while (stack_iterator_next(&it, &value)) {
        stack_push(right, value);
    }

    while (stack_pop(src, &value)) {}
}

static void merge_sorted_stacks(Stack *a, Stack *b, Stack *result) {
    StackIterator it_a = stack_iterator_begin(a);
    StackIterator it_b = stack_iterator_begin(b);
    int val_a, val_b;
    bool has_a = stack_iterator_next(&it_a, &val_a);
    bool has_b = stack_iterator_next(&it_b, &val_b);

    while (has_a && has_b) {
        if (val_a <= val_b) {
            stack_push(result, val_a);
            has_a = stack_iterator_next(&it_a, &val_a);
        } else {
            stack_push(result, val_b);
            has_b = stack_iterator_next(&it_b, &val_b);
        }
    }
    while (has_a) {
        stack_push(result, val_a);
        has_a = stack_iterator_next(&it_a, &val_a);
    }
    while (has_b) {
        stack_push(result, val_b);
        has_b = stack_iterator_next(&it_b, &val_b);
    }
}

void stack_merge_sort(Stack *s) {
    if (stack_size(s) <= 1) return;

    Stack left, right;
    stack_init(&left);
    stack_init(&right);

    split_stack(s, &left, &right);

    stack_merge_sort(&left);
    stack_merge_sort(&right);

    Stack merged;
    stack_init(&merged);
    merge_sorted_stacks(&left, &right, &merged);

    Stack temp;
    stack_init(&temp);
    int value;
    while (stack_pop(&merged, &value)) {
        stack_push(&temp, value);
    }
    while (stack_pop(&temp, &value)) {
        stack_push(s, value);
    }

    stack_destroy(&temp);
    stack_destroy(&merged);
    stack_destroy(&left);
    stack_destroy(&right);
}