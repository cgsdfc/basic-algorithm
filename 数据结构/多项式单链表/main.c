#include <stdio.h>
#include <stdlib.h>

/*
用单链表实现两个一元多项式的和。
*/

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct PolyNode {
    int exp;
    int cof;
    struct PolyNode* next;
} PolyNode;

int Compare(int a, int b) {
    return a == b ? 0 : (a > b ? 1 : -1);
}

void Append(int c, int e, PolyNode** rear) {
    PolyNode* n = malloc(sizeof(PolyNode));
    n->cof = c;
    n->exp = e;
    n->next = NULL;
    (*rear)->next = n;
    *rear = n;
}

/*
a,b 按照指数有序。
如果是指数递增，则a的指数小于b时，应插入a，因为要等a的指数变大以和b匹配。
如果是指数递减，则a的指数大于b时，应插入a，因为要等a的指数变小以和b匹配。
总之，多项式指数递增还是递减，决定了当a的一项不等于b的一项时，是插入a的项还是b的项。

注意：
1. 给结果多项式分配了头节点，方便实现Append操作，在函数返回之前，释放了头节点。
2. 如果没有头节点，则Append操作可能同时修改front和rear。
3.
结果多项式需要维护front和rear两个指针，rear用于实现Append操作，front用于返回结果。
*/

// 这里约定多项式是指数递减的。
PolyNode* Add(PolyNode* a, PolyNode* b) {
    PolyNode* front;
    PolyNode* rear;
    PolyNode* temp;
    front = rear = malloc(sizeof(PolyNode));
    int sum;

    while (a && b) {
        switch (Compare(a->exp, b->exp)) {
            case 1:
                // a>b
                Append(a->cof, a->exp, &rear);
                a = a->next;
                break;
            case -1:
                // b>a
                Append(b->cof, b->exp, &rear);
                b = b->next;
                break;
            case 0:
                sum = a->cof + b->cof;
                if (sum) { Append(sum, a->exp, &rear); }
                a = a->next;
                b = b->next;
                break;
        }
    }
    for (; a; a = a->next)
        Append(a->cof, a->exp, &rear);
    for (; b; b = b->next)
        Append(b->cof, b->exp, &rear);
    rear->next = NULL;
    // 去掉头节点。
    temp = front;
    front = front->next;
    free(temp);
    return front;
}

int main(int argc, char* argv[]) {
    return 0;
}
