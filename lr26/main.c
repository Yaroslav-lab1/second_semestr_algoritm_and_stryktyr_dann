#include <stdio.h>
#include "stack.h"
#include "stack_sort.h"
#include "queue.h"
#include "ringbuf.h"

void print_stack(const Stack *s) {
    StackIterator it = stack_iterator_begin(s);
    int value;
    printf("Стек (дно -> вершина): ");
    while (stack_iterator_next(&it, &value)) printf("%d ", value);
    printf("\n");
}

int main() {
    printf("=== Тестирование стека ===\n");
    Stack s;
    stack_init(&s);
    int test_data[] = {42, 17, 8, 99, 23, 5, 67, 31};
    int n = sizeof(test_data) / sizeof(test_data[0]);
    printf("Вталкиваю в стек: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", test_data[i]);
        stack_push(&s, test_data[i]);
    }
    printf("\n");
    print_stack(&s);
    stack_merge_sort(&s);
    printf("После сортировки слиянием:\n");
    print_stack(&s);
    printf("Извлечение: ");
    int val;
    while (stack_pop(&s, &val)) printf("%d ", val);
    printf("\n\n");
    stack_destroy(&s);

    printf("=== Тестирование очереди ===\n");
    Queue *q = queue_create();
    int queue_data[] = {10, 20, 30, 40, 50};
    n = sizeof(queue_data) / sizeof(queue_data[0]);
    printf("Добавляю в очередь: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", queue_data[i]);
        queue_enqueue(q, queue_data[i]);
    }
    printf("\nРазмер очереди: %d\n", queue_size(q));
    printf("Извлечение из очереди: ");
    while (queue_dequeue(q, &val)) {
        printf("%d ", val);
    }
    printf("\nОчередь пуста: %s\n\n", queue_is_empty(q) ? "да" : "нет");
    queue_destroy(q);

    printf("=== Тестирование кольцевого буфера ===\n");
    RingBuf rb;
    ringbuf_init(&rb);

    printf("Заполняю буфер (push_back): 1 2 3 4 5\n");
    ringbuf_push_back(&rb, 1);
    ringbuf_push_back(&rb, 2);
    ringbuf_push_back(&rb, 3);
    ringbuf_push_back(&rb, 4);
    ringbuf_push_back(&rb, 5);
    printf("Размер: %d, peek_front: ", ringbuf_size(&rb));
    int f, b;
    ringbuf_peek_front(&rb, &f);
    printf("%d, peek_back: ", f);
    ringbuf_peek_back(&rb, &b);
    printf("%d\n", b);

    printf("Добавляю в начало (push_front): 0\n");
    ringbuf_push_front(&rb, 0);
    printf("Размер: %d, peek_front: ", ringbuf_size(&rb));
    ringbuf_peek_front(&rb, &f);
    printf("%d\n", f);

    printf("Извлекаю с конца (pop_back): ");
    ringbuf_pop_back(&rb, &val);
    printf("%d\n", val);
    printf("Размер: %d, peek_back: ", ringbuf_size(&rb));
    ringbuf_peek_back(&rb, &b);
    printf("%d\n", b);

    printf("Извлекаю спереди (pop_front): ");
    ringbuf_pop_front(&rb, &val);
    printf("%d\n", val);
    printf("Размер: %d, peek_front: ", ringbuf_size(&rb));
    ringbuf_peek_front(&rb, &f);
    printf("%d\n", f);

    printf("Очищаю буфер: ");
    while (!ringbuf_is_empty(&rb)) {
        ringbuf_pop_front(&rb, &val);
        printf("%d ", val);
    }
    printf("\nБуфер пуст: %s\n", ringbuf_is_empty(&rb) ? "да" : "нет");

    ringbuf_destroy(&rb);
    return 0;
}