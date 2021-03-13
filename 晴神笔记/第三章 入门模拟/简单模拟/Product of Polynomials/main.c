#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// ������ߴ���Ϊ1000�Ķ���ʽ���,���������ݴ�Ϊ2000 
#define MAXN 2005 

/*
���˷�ֻ��Ҫ��������Ϳ�����.
һ����ŵ�һ������,��Ϊÿ�ζ�Ҫ������һ��������.
�ڶ�����Ž��,�����ۼ�.
����Ҫһ����Ų��ֻ���b,��Ϊ����ֱ���ۼӵ�d����.

��ų���������a�������Ż�Ϊ�ܼ��洢,��Ϊ��ʹ���������ͬ������Ҫ�ϲ�,
����˷��Ĺ���Ҳʵ���˺ϲ�. 
*/

double res[MAXN];

typedef struct Term {
	int exp;
	double cof;
} Term;

#define MAXK 15

int main(int argc, char *argv[]) {
	int n; // ��һ�������ĳ���. 
	Term a[MAXK]; // ��һ������. 
	int m; // �ڶ��������ĳ���. 
	int i;
	int j;
	
	freopen("./in.txt", "r", stdin);
	
	scanf("%d", &n);
	for (i=0;i<n;++i) {
		scanf("%d%lf", &a[i].exp, &a[i].cof);
	}
	
	scanf("%d", &m);
	for (i=0;i<m;++i) {
		int e;
		double c;
		scanf("%d%lf", &e, &c);
		for (j=0; j<n; ++j) {
			res[a[j].exp + e] += a[j].cof * c;
		}
	}
	// ����c�ķ�����. 
	n=0;
	for (i=0;i<MAXN;++i) {
		if (res[i]) ++n;
	}
	printf("%d", n);
	for (i=MAXN-1;i>=0;--i) {
		if (res[i]) {
			printf(" %d %.1f", i, res[i]);
		}
	}
	return 0;
}
