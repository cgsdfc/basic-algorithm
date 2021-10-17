#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
用链表表示的二叉树。
基本操作：前序遍历，中序遍历，后序遍历，层序遍历。
以及前三种遍历的非递归实现。
*/

typedef struct Node Node;
struct Node {
    int data;
    Node *left, *right;
};

// 递归式深度优先遍历可以实现前中后序遍历。
// 各节点的访问路径是一样的，每个节点有三次被访问的机会。
// 分别为：
// 1. 第一次遇到，即未访问n的任何子树。
// 2. 第二次遇到，访问完n的左子树，未访问n的右子树。
// 3. 第三次遇到，n的左右子树均访问完。
// 这三个时机就对应了三种前中后三种遍历。
// 在1时处理n的，即为前序遍历；在2时处理n的，即为中序遍历；在3时处理n的，即为后序遍历。
void PreOrderVisit(Node* node) {
    if (node) {
        // 时机1：先序遍历
        PreOrderVisit(node->left);
        // 时机2：中序遍历
        PreOrderVisit(node->right);
        // 时机3：后序遍历
    }
}

/*
非递归实现三种遍历
思想基础就是三种遍历其实就是深度优先遍历，并且它们访问各个节点的顺序完全相同，
只要用栈模拟这种访问顺序，并在代码中找到上述的三个时机，即可实现非递归的三种遍历。

首先需要实现栈的基本操作。并且以树的高度估计最大栈深。
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
算法基本思想：
1. 沿着左孩子一直往下走，走到头，把沿途的左孩子都压栈。
2. 接着折返，弹出一个节点A， 令当前节点等于A的有孩子。
3. 只要当前节点不空，或者栈不空，重复1，2步骤。
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
            // 时机1：先序遍历。
            PreOrder(node);
            Push(stack, node);
            node = node->left;
        }
        if (!IsEmpty(stack)) {
            node = Pop(stack);
            /*
            在一个节点到达时机2时，它的左孩子肯定刚刚过了时机3.
            */

            /*
            左孩子时机3，父节点时机2.
            右孩子时机3，父节点时机3.
            利用父子节点发生时机的关系，可以实现后续遍历。

            现在父节点是n，则n->left 3, n 2.
            现在把n->left作为父节点，则n->left->right 3 n->left 3
            */
            if (node->left) {
                // 右孩子时机3
                PostOrder(node->left->right);
            }

            // node->left的时机3：后续遍历。
            PostOrder(node->left);

            // node->left.
            // 时机2：中序遍历。
            InOrder(node);

            node = node->right;
            /*
            注意，n到了时机2时，恰好在n的左孩子的时机3之后。
            所以在n的时机2之前，先触发n->left的时机3.
            并且，n的右孩子到了时机3，下面就到n的时机3.
            */
        }
    }
}
