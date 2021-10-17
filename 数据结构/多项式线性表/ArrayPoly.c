#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
�����档
��������Ķ���ʽ�����˺ϲ�ͬ������ǿ���������ġ�
*/

/*
�Ѷ���ʽ��ϵ����ָ����Ϊһ���ṹ�����һ���������Լ��ϵ��Ϊ0��Ŀռ䡣
��ָ������洢ʱ������ʽ�ӷ���O(n)��
*/

typedef struct PolyNode {
    int co;
    int ep;
} PolyNode;

#define MAXN 100

typedef struct Poly {
    PolyNode data[MAXN];
    int last;  // ���һ��Ԫ�ص��±ꡣ
} Poly;

// ���ڶ�data����ȷ��PolyNode��ָ����������
static int CmpPolyNode(const void* a, const void* b) {
    return ((PolyNode*) a)->ep - ((PolyNode*) b)->ep;
}

// ����һ������ʽ��
static Poly* Create(int n, PolyNode ns[]) {
    int i;
    Poly* p = malloc(sizeof(struct Poly));
    p->last = n - 1;
    memcpy(&p->data, ns, sizeof(PolyNode) * n);
    qsort(&p->data, n, sizeof(PolyNode), &CmpPolyNode);
    return p;
}

Poly* CreateEmpty(void) {
    Poly* p = malloc(sizeof(Poly));
    memset(&p->data, 0, sizeof(p->data));
    p->last = -1;
    return p;
}

void AddTerm(Poly* p, PolyNode n) {
    // ���ɼ���ϵ��Ϊ0�
    if (n.co == 0) return;
    assert(p->last != MAXN - 1);
    ++p->last;
    p->data[p->last] = n;
}

Poly* Add(Poly* a, Poly* b) {
    int i, j;
    Poly* res = CreateEmpty();
    i = j = 0;
    int cmp;
    PolyNode nd = {};

    // �鲢����������㷨��
    while (i <= a->last || j <= b->last) {
        if (i <= a->last && j <= b->last) {
            cmp = a->data[i].ep - b->data[i].ep;
            if (cmp == 0) {
                nd.co = a->data[i].co + b->data[j].co;
                nd.ep = a->data[i].ep;
                ++i;
                ++j;
                AddTerm(res, nd);
            } else if (cmp < 0) {
                AddTerm(res, a->data[i++]);
            } else {
                AddTerm(res, b->data[j++]);
            }
        } else if (i <= a->last) {
            // b�Ѿ��ľ���
            AddTerm(res, a->data[i++]);
        } else if (j <= b->last) {
            // a�Ѿ��ľ���
            AddTerm(res, b->data[j++]);
        }
    }

    return res;
}

Poly* Read(void) {
    int n;
    int i;
    PolyNode ns[MAXN];
    Poly* res;

    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d%d", &ns[i].co, &ns[i].ep);
    }
    res = Create(n, ns);
    return res;
}

void Print(Poly* a) {
    int i;
    for (i = 0; i <= a->last; ++i) {
        printf("%d %d, ", a->data[i].co, a->data[i].ep);
    }
    puts("");
}

void TestPolyAdd(void) {
    freopen("./in.txt", "r", stdin);

    Poly* a = Read();
    Poly* b = Read();
    Poly* res = Add(a, b);
    Print(res);
}
