#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 100005

/*
在数组内部，先是负数，然后是正数。
负数和证书都按照绝对值从大到小排序。
0作为正数，排在最后面。 
*/ 
typedef struct List {
	int data[MAXN];
	int negs;
	int len;
} List;

List coupon, product;

int CMP(const void*_a, const void*_b) {
	int a=*(int*)_a;
	int b=*(int*)_b;
	
	if (a < 0 && b < 0) {
		return a-b;
	}
	if (a >= 0 && b >= 0) {
		return b-a;
	}
	// ab符号不同。负数在前，正数在后。 
	if (a < 0) return -1;
	return 1;
}

void Print(List* x) {
	int i;
	
	printf("len %d negs %d\n", x->len, x->negs);
	for (i=0;i<x->len;++i) {
		printf("%d ", x->data[i]);
	}
	puts("");
}

void Read(List* x) {
	int i;
	
	x->negs=0;
	scanf("%d", &x->len);
	for (i=0;i<x->len;++i) {
		int v;
		scanf("%d",&v);
		x->data[i]=v;
		if (v<0) {
			++x->negs;
		}
	}
	qsort(&x->data, x->len, sizeof(int), CMP); 
	
//	Print(x);
}

int FindMax(List* a, List* b) {
	int ans=0;
	int i;
	int j;
	
	// 先计算负负得正的和。 
	for (i=0;i<a->negs&&i<b->negs;++i) {
		ans += a->data[i] * b->data[i];
	}
	
	for (i=a->negs,j=b->negs; i<a->len && j<b->len; ++i, ++j) {
		ans += a->data[i] * b->data[j];
	}
	
	return ans;
}

int main(int argc, char *argv[]) {
	int res;
	
	freopen("./in.txt","r",stdin);
	
	Read(&coupon);
	Read(&product);
	res=FindMax(&coupon, &product);
	printf("%d\n", res);
	
	return 0;
}
