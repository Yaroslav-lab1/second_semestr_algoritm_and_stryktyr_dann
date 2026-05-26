#include "queue.h"
#include "stack.h"
#include <stdlib.h>

struct Queue {
    Stack in;
    Stack out;
};

Queue* queue_create(void) {
    Queue *q = (Queue*) malloc(sizeof(Queue));
    if (q) {
        stack_init(&q->in);
        stack_init(&q->out);
    }
    return q;
}

void queue_destroy(Queue *q) {
    if (q) {
        stack_destroy(&q->in);
        stack_destroy(&q->out);
        free(q);
    }
}

bool queue_enqueue(Queue *q, int value) {
    return stack_push(&q->in, value);
}

bool queue_dequeue(Queue *q, int *out_value) {
    if (queue_is_empty(q)) return false;

    if (stack_is_empty(&q->out)) {
        int val;
        while (stack_pop(&q->in, &val)) {
            stack_push(&q->out, val);
        }
    }
    return stack_pop(&q->out, out_value);
}

bool queue_is_empty(const Queue *q) {
    return stack_is_empty(&q->in) && stack_is_empty(&q->out);
}

int queue_size(const Queue *q) {
    return stack_size(&q->in) + stack_size(&q->out);
}