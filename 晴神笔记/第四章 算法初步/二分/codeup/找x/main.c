#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 205

/*
����Ҫ�����Ԫ��x��Ȼ�����x��ԭ������±꣬
����ʹ�ö��ֲ��ҡ�

�ýṹ���¼Ԫ�ص�ֵ���±꣬������ʱ��Ϊ�˱�����ȵ�ֵ��˳��
��ԭ�����еĲ�ͬ����CMP��ʹ��˫�ر�׼�����򣬾Ϳ��Ա�֤��һ�㡣
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
Ҫ�ҵ����ڵ���x�ĵ�һ��Ԫ�أ�������Ԫ��������ڲ��ҵ���x��
��һ����ԭ�������������x�ĵ�һ��Ԫ�ء�
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
		дSizeOfElem����ʱ�����ֱ��дԪ�����ͣ������׳���
		���룬Ԫ�����ͱ��ˣ�����ȴ���˸ġ�дsizeof(a[0])���Զ����ġ�
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
