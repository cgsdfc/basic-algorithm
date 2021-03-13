#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN (2*100000 + 5)

typedef struct List {
	int data[MAXN];
	int len;
} List;

List A, B;

int CMP(const void*_a, const void*_b) {
	return *(int*)_a-*(int*)_b;
}

void Read(List* ls) {
	int i;
	scanf("%d",&ls->len);
	for (i=0;i<ls->len;++i) {
		scanf("%d",&ls->data[i]);
	}
	// 题目保证两个序列都是递增的。不必排序。 
	qsort(ls->data, ls->len, sizeof(int), CMP);
}

int GetMid(int len) {
	if (len & 1) return len/2;
	else return len/2 - 1;
}

int main(int argc, char *argv[]) {
	int m;
	int i;
	int j;
	int k;
	int ans;
	
	Read(&A);
	Read(&B);
	
	m=GetMid(A.len+B.len);
	i=j=k=0;
	
	while (i<A.len && j<B.len && k<=m) {
		if (A.data[i] <= B.data[j]) {
			ans=A.data[i++];
			++k;
		} else {
			ans=B.data[j++];
			++k;
		}
	}
	while (i<A.len && k<=m) {
		ans=A.data[i++];
		++k;
	}
	while (j<B.len && k<=m) {
		ans=B.data[j++];
		++k;
	}
	printf("%d\n", ans);
	
	return 0;
}
