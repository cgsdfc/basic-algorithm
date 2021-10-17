#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

// ��̬���ȵ�˳���
typedef struct List {
    int data[MAXN];
    int last;  // ָʾ���һ��Ԫ���±ꡣ
} List;

List* Create(void) {
    List* l = malloc(sizeof(List));
    l->last = -1;
    return l;
}

void Free(List* l) {
    free(l);
}

int Size(List* l) {
    return l->last + 1;
}

int Empty(List* l) {
    return 0 == Size(l);
}

//����ռ�����
int Full(List* l) {
    return MAXN == Size(l);
}

// ����λ��Ϊi��Ԫ�أ�λ���1��n��
int FindKth(List* l, int i) {
    assert(!Empty(l));
    assert(1 <= i && i <= Size(l));
    return l->data[i - 1];
}

//����Ԫ��ֵΪx��λ��
int Find(List* l, int x) {
    int i;
    for (i = 0; i <= l->last; ++i) {
        if (l->data[i] == x) return i + 1;
    }
    return 0;
}

//��λ��i������Ԫ��x��ʹ��x��Ϊλ��i����Ԫ�ء�
// i�ķ�Χ��1��n+1 .
void Insert(List* l, int i, int x) {
    int j;
    assert(!Full(l));
    assert(1 <= i && i <= Size(l) + 1);

    for (j = l->last; j >= i - 1; j--) {
        l->data[j + 1] = l->data[j];
    }
    l->data[i - 1] = x;
    ++l->last;
}

//ɾ��λ��Ϊi��Ԫ��,������ֵ.
int Remove(List* l, int i) {
    int j;
    int x;
    assert(!Empty(l));
    assert(1 <= i && i <= l->last);

    x = l->data[i - 1];
    for (j = i; j <= l->last; ++j) {
        l->data[j - 1] = l->data[j];
    }
    l->last--;
    return x;
}

List* Read(void) {
    int n;
    int i;
    List* l;

    l = Create();
    scanf("%d", &n);
    l->last = n - 1;
    for (i = 0; i < n; ++i) {
        scanf("%d", &l->data[i]);
    }
    return l;
}

//�ҵ�l����СԪ,ɾ��֮,��λ�����һ��Ԫ���,������Сֵ.
void RemoveMin(List* l) {
    int i;
    int min = l->data[0];
    int pos = 0;

    assert(!Empty(l));
    for (i = 0; i <= l->last; ++i) {
        if (l->data[i] < min) {
            min = l->data[i];
            pos = i;
        }
    }
    l->data[pos] = l->data[l->last];
    --l->last;
    return min;
}

//ԭ��ɾ��l��ֵΪx������Ԫ��,Ҫ��ʱ����O(n).
void RemoveAll(List* l, int x) {
    int i, j;
    //	˫ָ�뷨: iɨ����������,j�ռ���xԪ��.
    for (i = 0, j = 0; i <= l->last; ++i) {
        if (l->data[i] != x) { l->data[j++] = l->data[i]; }
    }
    l->last = j - 1;
}

//ԭ����תl��
void Reverse(List* l) {
    int i;
    if (Empty(l)) return;
    // -1/2 == 0 �������.
    for (i = 0; i <= l->last / 2; ++i) {
        int tmp = l->data[i];
        l->data[i] = l->data[l->last - i];
        l->data[l->last - i] = tmp;
    }
}

int CmpElem(const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

void Sort(List* l) {
    qsort(l->data, Size(l), sizeof(int), CmpElem);
}

void Unique(List* l) {
    int i, k;

    if (Empty(l) || 1 == Size(l)) return;
    Sort(l);
    //	iָ��ǰԪ��,ɨ����������.
    //	kָ��ǰ���ظ����е����һ��Ԫ��,Ҫ��������е�ĩβ����Ԫ��,����++k
    for (i = 1, k = 0; i <= l->last; ++i) {
        if (l->data[i] != l->data[k]) {
            // ע�������++k,��Ϊ��һ��Ԫ�ر��뱣��.
            l->data[++k] = l->data[i];
        }
    }
    //	k��Ԫ�ص��±�,����Ҫ-1.
    l->last = k;
}

void Print(List* l) {
    int i;
    for (i = 0; i <= l->last; ++i) {
        printf("%d ", l->data[i]);
    }
    puts("");
}

void TestListBasic(void) {
    List* l;
    int i;

    l = Create();
    for (i = 0; i < 5; ++i) {
        Insert(l, 1, i);
    }
    printf("size:%d\n", Size(l));
    Print(l);
}

void TestListReverse(void) {
    List* l;

    l = Read();
    Reverse(l);
    Print(l);
}

void TestListUnique(void) {
    List* l;

    l = Read();
    Unique(l);
    Print(l);
}

void TestRemoveAll(void) {
    List* l;
    int x;

    l = Read();
    scanf("%d", &x);
    RemoveAll(l, x);
    Print(l);
}
