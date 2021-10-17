#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
�������ʾ�Ķ�������
����������ǰ����������������������������������
�Լ�ǰ���ֱ����ķǵݹ�ʵ�֡�
*/

typedef struct Node Node;
struct Node {
    int data;
    Node *left, *right;
};

// �ݹ�ʽ������ȱ�������ʵ��ǰ�к��������
// ���ڵ�ķ���·����һ���ģ�ÿ���ڵ������α����ʵĻ��ᡣ
// �ֱ�Ϊ��
// 1. ��һ����������δ����n���κ�������
// 2. �ڶ���������������n����������δ����n����������
// 3. ������������n�����������������ꡣ
// ������ʱ���Ͷ�Ӧ������ǰ�к����ֱ�����
// ��1ʱ����n�ģ���Ϊǰ���������2ʱ����n�ģ���Ϊ�����������3ʱ����n�ģ���Ϊ���������
void PreOrderVisit(Node* node) {
    if (node) {
        // ʱ��1���������
        PreOrderVisit(node->left);
        // ʱ��2���������
        PreOrderVisit(node->right);
        // ʱ��3���������
    }
}

/*
�ǵݹ�ʵ�����ֱ���
˼������������ֱ�����ʵ����������ȱ������������Ƿ��ʸ����ڵ��˳����ȫ��ͬ��
ֻҪ��ջģ�����ַ���˳�򣬲��ڴ������ҵ�����������ʱ��������ʵ�ַǵݹ�����ֱ�����

������Ҫʵ��ջ�Ļ������������������ĸ߶ȹ������ջ�
*/

#define MAXSIZE 100

typedef Node* ElemType;

typedef struct ArrayStack {
    ElemType data[MAXSIZE];
    int top;
} * Stack;

static Stack CreateStack(void) {
    Stack s = malloc(sizeof(struct ArrayStack));
    s->top = -1;  // Init empty.
    return s;
}

static int IsEmpty(Stack s) {
    return s->top == -1;
}

static void Push(Stack s, ElemType item) {
    if (s->top == MAXSIZE - 1) {
        printf("OverflowError");
        return;
    }
    s->data[++s->top] = item;
}

static ElemType Pop(Stack s) {
    if (IsEmpty(s)) {
        printf("UnderflowError");
        return -1;
    }
    return s->data[s->top--];
}

static ElemType Top(Stack s) {
    if (IsEmpty(s)) {
        printf("UnderflowError");
        return -1;
    }
    return s->data[s->top];
}

/*
�㷨����˼�룺
1. ��������һֱ�����ߣ��ߵ�ͷ������;�����Ӷ�ѹջ��
2. �����۷�������һ���ڵ�A�� �ǰ�ڵ����A���к��ӡ�
3. ֻҪ��ǰ�ڵ㲻�գ�����ջ���գ��ظ�1��2���衣
*/

void PreOrder(Node* node) {
    if (node) { printf("%d\n", node->data); }
}
void InOrder(Node* node) {
    if (node) { printf("%d\n", node->data); }
}
void PostOrder(Node* node) {
    if (node) { printf("%d\n", node->data); }
}

void IterVisit(Node* node) {
    Stack stack = CreateStack();

    while (node || !IsEmpty(stack)) {
        while (node) {
            // ʱ��1�����������
            PreOrder(node);
            Push(stack, node);
            node = node->left;
        }
        if (!IsEmpty(stack)) {
            node = Pop(stack);
            /*
            ��һ���ڵ㵽��ʱ��2ʱ���������ӿ϶��ոչ���ʱ��3.
            */

            /*
            ����ʱ��3�����ڵ�ʱ��2.
            �Һ���ʱ��3�����ڵ�ʱ��3.
            ���ø��ӽڵ㷢��ʱ���Ĺ�ϵ������ʵ�ֺ���������

            ���ڸ��ڵ���n����n->left 3, n 2.
            ���ڰ�n->left��Ϊ���ڵ㣬��n->left->right 3 n->left 3
            */
            if (node->left) {
                // �Һ���ʱ��3
                PostOrder(node->left->right);
            }

            // node->left��ʱ��3������������
            PostOrder(node->left);

            // node->left.
            // ʱ��2�����������
            InOrder(node);

            node = node->right;
            /*
            ע�⣬n����ʱ��2ʱ��ǡ����n�����ӵ�ʱ��3֮��
            ������n��ʱ��2֮ǰ���ȴ���n->left��ʱ��3.
            ���ң�n���Һ��ӵ���ʱ��3������͵�n��ʱ��3.
            */
        }
    }
}
