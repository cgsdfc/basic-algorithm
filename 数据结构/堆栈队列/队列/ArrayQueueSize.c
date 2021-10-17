#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
用顺序表（静态数组）实现的队列。
用 size 判空和判满，可以不用空出一个位置。
*/

#define MAXSIZE 10

typedef struct QueueImplHead {
    int data[MAXSIZE];
    int front;
    int rear;
    int size;
} * Queue;

static Queue Create(void) {
    Queue q = malloc(sizeof(struct QueueImplHead));
    // front指示队首元素前一个，rear指示队尾元素。
    q->front = q->rear = 0;
    q->size = 0;
    return q;
}

static int Size(Queue q) {
    return q->size;
}

static int Empty(Queue q) {
    return 0 == Size(q);
}

static int Full(Queue q) {
    return MAXSIZE == Size(q);
}

static void PushQueue(Queue q, int item) {
    assert(!Full(q));
    q->rear = (q->rear + 1) % MAXSIZE;
    q->data[q->rear] = item;
    ++q->size;
}

static int PopQueue(Queue q) {
    assert(!Empty(q));
    q->front = (q->front + 1) % MAXSIZE;
    --q->size;
    return q->data[q->front];
}

static int Front(Queue q) {
    assert(!Empty(q));
    return q->data[(q->front + 1) % MAXSIZE];
}

static int Rear(Queue q) {
    assert(!Empty(q));
    return q->data[q->rear];
}

static void Print(Queue q) {
    printf("front=%d\n", q->front);
    printf("rear=%d\n", q->rear);
    printf("size=%d\n", q->size);
}

void TestArrayQueueSize(void) {
    int i;
    Queue q = Create();

    assert(Empty(q));
    for (i = 1; i <= MAXSIZE; ++i) {
        PushQueue(q, 1);
        Print(q);
    }
    assert(Full(q));

    for (i = 1; i <= MAXSIZE; ++i) {
        PopQueue(q);
        Print(q);
    }
    assert(Empty(q));

    for (i = 1; i <= 3; ++i) {
        PushQueue(q, i);
    }
    assert(Size(q) == 3);

    for (i = 1; i <= 3; ++i) {
        assert(PopQueue(q) == i);
    }
}
