#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct Queue Queue;

Queue* queue_create(void);
void queue_destroy(Queue *q);
bool queue_enqueue(Queue *q, int value);
bool queue_dequeue(Queue *q, int *out_value);
bool queue_is_empty(const Queue *q);
int queue_size(const Queue *q);

#endif