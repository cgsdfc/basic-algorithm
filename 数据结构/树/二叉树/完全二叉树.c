/*
完全二叉树可以用数组保存。
保存方法是按层序保存。堆就是一种完全二叉树
如：
1
2 3
4 5 6 7
是一棵完全二叉树。
则保存为：
1 2 3 4 5 6 7
给定一个节点的下标，可以方便的计算出它的孩子和父节点的下标。
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

typedef struct Node {
    int data;
} Node;

// 所有的节点编号为0到size-1.
typedef struct Tree {
    Node node[MAXN];
    int size;
} Tree;

// 带上下标检查，防止越界。
Node* GetNode(Tree* tr, int i) {
    assert(0 <= i && i < tr->size);
    return &tr->node[i];
}

// 左孩子在2i+1
Node* Left(Tree* tr, int i) {
    return GetNode(tr, 2 * i + 1);
}

int HasLeft(Tree* tr, int i) {
    int v = 2 * i + 1;
    return 0 <= v && v < tr->size;
}

Node* Right(Tree* tr, int i) {
    return GetNode(tr, 2 * i);
}

Node* Parent(Tree* tr, int i) {
    // 0号是根，没有父节点。
    assert(i != 0);
    return GetNode(tr, i / 2);
}
