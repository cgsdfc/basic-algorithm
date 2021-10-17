#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

// 静态长度的顺序表。
typedef struct List {
    int data[MAXN];
    int last;  // 指示最后一个元素下标。
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

//数组空间满。
int Full(List* l) {
    return MAXN == Size(l);
}

// 查找位序为i的元素，位序从1到n。
int FindKth(List* l, int i) {
    assert(!Empty(l));
    assert(1 <= i && i <= Size(l));
    return l->data[i - 1];
}

//查找元素值为x的位序。
int Find(List* l, int x) {
    int i;
    for (i = 0; i <= l->last; ++i) {
        if (l->data[i] == x) return i + 1;
    }
    return 0;
}

//在位序i处插入元素x，使得x成为位序i处的元素。
// i的范围是1到n+1 .
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

//删除位序为i的元素,返回其值.
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

//找到l的最小元,删除之,空位用最后一个元素填补,返回最小值.
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

//原地删除l中值为x的所有元素,要求时间是O(n).
void RemoveAll(List* l, int x) {
    int i, j;
    //	双指针法: i扫描整个序列,j收集非x元素.
    for (i = 0, j = 0; i <= l->last; ++i) {
        if (l->data[i] != x) { l->data[j++] = l->data[i]; }
    }
    l->last = j - 1;
}

//原地逆转l。
void Reverse(List* l) {
    int i;
    if (Empty(l)) return;
    // -1/2 == 0 会出问题.
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
    //	i指向当前元素,扫描整个序列.
    //	k指向当前无重复序列的最后一个元素,要在这个序列的末尾加入元素,必须++k
    for (i = 1, k = 0; i <= l->last; ++i) {
        if (l->data[i] != l->data[k]) {
            // 注意这里的++k,因为第一个元素必须保留.
            l->data[++k] = l->data[i];
        }
    }
    //	k是元素的下标,不需要-1.
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
