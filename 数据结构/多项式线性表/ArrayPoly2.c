#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
增强版
在构造时对多项式进行合并同类项和去掉非零项，
因此允许任何输入的多项式。 
*/

typedef struct PolyNode {
	int co;
	int ep;
} PolyNode;

typedef struct Poly {
	PolyNode* data;
	int last; // 最后一个元素的下标。	
} Poly;

// 用于对data排序，确保PolyNode按指数递增排序。 
static 
int CmpPolyNode(const void* a, const void* b) {
	return ((PolyNode*)a)->ep - ((PolyNode*)b)->ep;
}

// 按指数递增排序。 
void Sort(Poly* p) {
	qsort(p->data, p->last+1, sizeof(PolyNode), CmpPolyNode);
}

// 合并同类项。 
void Merge(Poly* p) {
	int i, k;
	Sort(p);
	
	// 有序数组去重。 
	for (i=1,k=0; i<=p->last; ++i) {
		PolyNode cur=p->data[i];
		if (cur.ep == p->data[k].ep) {
			p->data[k].co += cur.co;
		} else {
			p->data[++k] = cur;
		}
	}
	
	p->last=k;
	
}

// Remove all term with 0 co.
void DropZero(Poly* p) {
	int i,k;
	for (i=0,k=0; i<=p->last; ++i) {
		if (p->data[i].co) {
			p->data[k++]=p->data[i];
		}
	}
	p->last=k-1;
}

void Normal(Poly* p) {
	Merge(p);
	DropZero(p);
}

static
Poly* Create(int n) {
	Poly* p=malloc(sizeof(Poly));
	p->last=n-1;
	p->data=malloc(sizeof(PolyNode) * n);
	return p;	
}

static
int Size(Poly* p) {
	return p->last+1;
}

static
void Print(Poly* a) {
	int i;
	for (i=0;i<=a->last;++i) {
		printf("%d %d, ", a->data[i].co, a->data[i].ep);
	}
	puts("");
}

static
Poly* Add(Poly* a, Poly* b) {
	Poly* c=Create(Size(a) + Size(b));
	memcpy(c->data, a->data, sizeof(PolyNode) * Size(a));
	memcpy(c->data + Size(a), b->data, sizeof(PolyNode) * Size(b));
//	Print(c);
	Normal(c);
	return c;
}

static
Poly* Read(void) {
	int n;
	int i;
	Poly* res;
	
	scanf("%d", &n);
	res=Create(n);
	
	for (i=0;i<n;++i) {
		scanf("%d%d", &res->data[i].co, &res->data[i].ep);
	}
	return res;
}

void TestMerge(void) {
	Poly* p=Read();
	Merge(p);
	Print(p);
}

void TestDropZero(void) {
	Poly* p=Read();
	DropZero(p);
	Print(p);
}

void TestNormal(void) {
	Poly* p=Read();
	Normal(p);
	Print(p);
}

void TestPolyAdd2(void) {	
	Poly* a=Read();
	Poly* b=Read();
	Poly* res=Add(a, b);
	Print(res);
}

