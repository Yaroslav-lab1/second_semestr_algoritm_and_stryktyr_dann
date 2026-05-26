#include "ringbuf.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 4

void ringbuf_init(RingBuf *rb) {
    rb->data = (int*) malloc(INITIAL_CAPACITY * sizeof(int));
    rb->head = 0;
    rb->tail = 0;
    rb->size = 0;
    rb->capacity = INITIAL_CAPACITY;
}

void ringbuf_destroy(RingBuf *rb) {
    free(rb->data);
    rb->data = NULL;
    rb->head = 0;
    rb->tail = 0;
    rb->size = 0;
    rb->capacity = 0;
}

bool ringbuf_is_empty(const RingBuf *rb) {
    return rb->size == 0;
}

bool ringbuf_is_full(const RingBuf *rb) {
    return rb->size == rb->capacity;
}

int ringbuf_size(const RingBuf *rb) {
    return rb->size;
}

static bool ringbuf_resize(RingBuf *rb) {
    int new_capacity = rb->capacity * 2;
    int *new_data = (int*) malloc(new_capacity * sizeof(int));
    if (!new_data) return false;

    for (int i = 0; i < rb->size; i++) {
        new_data[i] = rb->data[(rb->head + i) % rb->capacity];
    }
    free(rb->data);
    rb->data = new_data;
    rb->head = 0;
    rb->tail = rb->size;
    rb->capacity = new_capacity;
    return true;
}

bool ringbuf_push_back(RingBuf *rb, int value) {
    if (ringbuf_is_full(rb) && !ringbuf_resize(rb)) {
        return false;
    }
    rb->data[rb->tail] = value;
    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->size++;
    return true;
}

bool ringbuf_pop_front(RingBuf *rb, int *out) {
    if (ringbuf_is_empty(rb)) return false;
    *out = rb->data[rb->head];
    rb->head = (rb->head + 1) % rb->capacity;
    rb->size--;
    return true;
}

bool ringbuf_push_front(RingBuf *rb, int value) {
    if (ringbuf_is_full(rb) && !ringbuf_resize(rb)) {
        return false;
    }
    rb->head = (rb->head - 1 + rb->capacity) % rb->capacity;
    rb->data[rb->head] = value;
    rb->size++;
    return true;
}

bool ringbuf_pop_back(RingBuf *rb, int *out) {
    if (ringbuf_is_empty(rb)) return false;
    rb->tail = (rb->tail - 1 + rb->capacity) % rb->capacity;
    *out = rb->data[rb->tail];
    rb->size--;
    return true;
}

bool ringbuf_peek_front(const RingBuf *rb, int *out) {
    if (ringbuf_is_empty(rb)) return false;
    *out = rb->data[rb->head];
    return true;
}

bool ringbuf_peek_back(const RingBuf *rb, int *out) {
    if (ringbuf_is_empty(rb)) return false;
    int idx = (rb->tail - 1 + rb->capacity) % rb->capacity;
    *out = rb->data[idx];
    return true;
}