#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
不带头节点的链接队列。
注意：front 指向队头，而rear指向队尾，因为队尾只能插入，不能删除，
而队头既能插入又能删除。
*/

// 队列节点。
typedef struct QNode {
  int data;
  struct QNode *next;
} QNode;

typedef struct LinkQueue {
  QNode *front;
  QNode *rear;
} * Queue;

static Queue Create() {
  Queue q = malloc(sizeof(struct LinkQueue));
  q->front = q->rear = NULL;
  return q;
}

static int Empty(Queue q) { return q->front == NULL; }

static void PushQueue(Queue q, int item) {
  // Allocate a node first.
  QNode *n = malloc(sizeof(QNode));
  n->data = item;
  n->next = NULL;

  // 尾插法。
  if (Empty(q)) {
    q->front = q->rear = n;
  } else {
    q->rear->next = n;
    q->rear = n;
  }
}

static int PopQueue(Queue q) {
  QNode *n;
  int item;

  assert(!Empty(q));
  n = q->front;
  item = n->data;

  if (q->front == q->rear) {
    // Only one element. After pop, will be empty.
    q->front = q->rear = NULL;
  } else {
    q->front = n->next;
  }
  free(n);
  return item;
}

void TestLinkQueue(void) {
  Queue q;
  int i;

  q = Create();
  assert(Empty(q));

  for (i = 0; i < 5; ++i) {
    PushQueue(q, i);
  }
  for (i = 0; i < 5; ++i) {
    assert(i == PopQueue(q));
  }
  assert(Empty(q));
}
