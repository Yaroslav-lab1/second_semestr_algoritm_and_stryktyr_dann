#ifndef RINGBUF_H
#define RINGBUF_H

#include <stdbool.h>

typedef struct {
    int *data;
    int head;
    int tail;
    int size;
    int capacity;
} RingBuf;

void ringbuf_init(RingBuf *rb);
void ringbuf_destroy(RingBuf *rb);
bool ringbuf_is_empty(const RingBuf *rb);
bool ringbuf_is_full(const RingBuf *rb);
int ringbuf_size(const RingBuf *rb);
bool ringbuf_push_back(RingBuf *rb, int value);
bool ringbuf_pop_front(RingBuf *rb, int *out);
bool ringbuf_push_front(RingBuf *rb, int value);
bool ringbuf_pop_back(RingBuf *rb, int *out);
bool ringbuf_peek_front(const RingBuf *rb, int *out);
bool ringbuf_peek_back(const RingBuf *rb, int *out);

#endif