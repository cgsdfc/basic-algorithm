#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 两个最高次幂为1000的多项式相乘,结果的最高幂次为2000 
#define MAXN 2005 

/*
做乘法只需要两个数组就可以了.
一个存放第一个乘数,因为每次都要遍历第一个乘数的.
第二个存放结果,用于累加.
不需要一个存放部分积的b,因为可以直接累加到d里面.

存放乘数的数组a还可以优化为密集存储,因为即使输入乘数有同类项需要合并,
计算乘法的过程也实现了合并. 
*/

double res[MAXN];

typedef struct Term {
	int exp;
	double cof;
} Term;

#define MAXK 15

int main(int argc, char *argv[]) {
	int n; // 第一个乘数的长度. 
	Term a[MAXK]; // 第一个乘数. 
	int m; // 第二个乘数的长度. 
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
	// 计算c的非零项. 
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
