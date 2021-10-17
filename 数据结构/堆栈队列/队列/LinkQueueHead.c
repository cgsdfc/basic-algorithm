#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
带头节点的链接队列。
有了头节点，可以简化插入删除的操作。
*/

// 队列节点。
typedef struct QNode {
    int data;
    struct QNode* next;
} QNode;

typedef struct LinkQueue {
    QNode* front;
    QNode* rear;
} * Queue;

static Queue Create(void) {
    Queue q = malloc(sizeof(struct LinkQueue));
    // 头节点，数据无意义。
    QNode* n = malloc(sizeof(QNode));
    memset(n, 0, sizeof(QNode));
    q->front = q->rear = n;
    return q;
}

static int Empty(Queue q) {
    // 注意rear->next == NULL不意味着队列为空。
    return q->front->next == NULL;
}

static void PushQueue(Queue q, int item) {
    QNode* n;

    n = malloc(sizeof(QNode));
    //	rear指向最后一个节点。
    n->data = item;
    n->next = NULL;
    q->rear->next = n;
    q->rear = n;
}

static int PopQueue(Queue q) {
    int item;
    QNode* n;

    assert(!Empty(q));
    //	front指向的是头节点。
    //	注意 第一个节点是 q->front->next，不是q->front。
    n = q->front->next;
    q->front->next = n->next;
    item = n->data;
    free(n);
    return item;
}

static int Front(Queue q) {
    assert(!Empty(q));
    return q->front->next->data;
}

static int Rear(Queue q) {
    assert(!Empty(q));
    return q->rear->data;
}

static void Free(Queue q) {
    QNode* n = q->front;
    while (n) {
        QNode* cur = n;
        n = n->next;
        free(cur);
    }
    q->front = q->rear = NULL;
}

void TestLinkQueueHead(void) {
    Queue q;
    int i;

    q = Create();
    assert(Empty(q));

    for (i = 0; i < 5; ++i) {
        PushQueue(q, i);
    }
    printf("front=%d\n", Front(q));
    printf("rear=%d\n", Rear(q));

    for (i = 0; i < 5; ++i) {
        assert(i == PopQueue(q));
    }
    assert(Empty(q));
}
