#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 205

/*
本题要求查找元素x，然后输出x在原数组的下标，
并且使用二分查找。

用结构体记录元素的值和下标，在排序时，为了避免相等的值的顺序
和原数组中的不同，在CMP中使用双重标准来排序，就可以保证这一点。
*/

typedef struct Node {
	int val;
	int pos;
} Node;

Node a[MAXN];

int CMP(const void*_a, const void*_b) {
	Node* a=(Node*)_a;
	Node* b=(Node*)_b;
	if (a->val != b->val) return a->val-b->val;
	return a->pos-b->pos;
}

/*
要找到大于等于x的第一个元素，这样的元素如果存在并且等于x，
则一定是原来数列里面等于x的第一个元素。
*/
int lower_bound(int left, int right, int x) {
	int mid;
	while (left < right) {
		mid=(left+right)/2;
		if (a[mid].val >= x) {
			right=mid;
		} else {
			left=mid+1;
		}
	}
	return left;
}

void Print(int n) {
	int i;
	for (i=0;i<n;++i) {
		printf("pos %d val %d\n", a[i].pos, a[i].val);
	}
}

int main(int argc, char *argv[]) {
	int n;
		
	while (scanf("%d",&n) != EOF) {
		int i;
		int res;
		int x;
		
		for (i=0;i<n;++i) {
			scanf("%d",&a[i].val);
			a[i].pos=i;
		}
		
//		Print(n);
		
		scanf("%d",&x);
		/*
		写SizeOfElem参数时，如果直接写元素类型，则容易出错，
		试想，元素类型变了，这里却忘了改。写sizeof(a[0])则自动更改。
		*/ 
		qsort(a, n, sizeof(a[0]), CMP);
		
		res=lower_bound(0, n, x);
		if (res != n && a[res].val == x) {
			printf("%d\n", a[res].pos);
		} else {
			puts("-1");
		}
	}
	
	return 0;
}
