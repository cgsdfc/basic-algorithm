#include <stdio.h>
#include <stdlib.h>

/*
�õ�����ʵ������һԪ����ʽ�ĺ͡�
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
a,b ����ָ������
�����ָ����������a��ָ��С��bʱ��Ӧ����a����ΪҪ��a��ָ������Ժ�bƥ�䡣
�����ָ���ݼ�����a��ָ������bʱ��Ӧ����a����ΪҪ��a��ָ����С�Ժ�bƥ�䡣
��֮������ʽָ���������ǵݼ��������˵�a��һ�����b��һ��ʱ���ǲ���a�����b���

ע�⣺
1. ���������ʽ������ͷ�ڵ㣬����ʵ��Append�������ں�������֮ǰ���ͷ���ͷ�ڵ㡣
2. ���û��ͷ�ڵ㣬��Append��������ͬʱ�޸�front��rear��
3.
�������ʽ��Ҫά��front��rear����ָ�룬rear����ʵ��Append������front���ڷ��ؽ����
*/

// ����Լ������ʽ��ָ���ݼ��ġ�
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
    // ȥ��ͷ�ڵ㡣
    temp = front;
    front = front->next;
    free(temp);
    return front;
}

int main(int argc, char* argv[]) {
    return 0;
}
