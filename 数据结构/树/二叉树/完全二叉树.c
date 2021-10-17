/*
��ȫ���������������鱣�档
���淽���ǰ����򱣴档�Ѿ���һ����ȫ������
�磺
1
2 3
4 5 6 7
��һ����ȫ��������
�򱣴�Ϊ��
1 2 3 4 5 6 7
����һ���ڵ���±꣬���Է���ļ�������ĺ��Ӻ͸��ڵ���±ꡣ
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

typedef struct Node {
    int data;
} Node;

// ���еĽڵ���Ϊ0��size-1.
typedef struct Tree {
    Node node[MAXN];
    int size;
} Tree;

// �����±��飬��ֹԽ�硣
Node* GetNode(Tree* tr, int i) {
    assert(0 <= i && i < tr->size);
    return &tr->node[i];
}

// ������2i+1
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
    // 0���Ǹ���û�и��ڵ㡣
    assert(i != 0);
    return GetNode(tr, i / 2);
}
