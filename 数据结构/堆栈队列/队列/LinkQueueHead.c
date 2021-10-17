#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
��ͷ�ڵ�����Ӷ��С�
����ͷ�ڵ㣬���Լ򻯲���ɾ���Ĳ�����
*/

// ���нڵ㡣
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
    // ͷ�ڵ㣬���������塣
    QNode* n = malloc(sizeof(QNode));
    memset(n, 0, sizeof(QNode));
    q->front = q->rear = n;
    return q;
}

static int Empty(Queue q) {
    // ע��rear->next == NULL����ζ�Ŷ���Ϊ�ա�
    return q->front->next == NULL;
}

static void PushQueue(Queue q, int item) {
    QNode* n;

    n = malloc(sizeof(QNode));
    //	rearָ�����һ���ڵ㡣
    n->data = item;
    n->next = NULL;
    q->rear->next = n;
    q->rear = n;
}

static int PopQueue(Queue q) {
    int item;
    QNode* n;

    assert(!Empty(q));
    //	frontָ�����ͷ�ڵ㡣
    //	ע�� ��һ���ڵ��� q->front->next������q->front��
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
