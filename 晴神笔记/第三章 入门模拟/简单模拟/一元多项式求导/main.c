#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
// ����ʽ��һ��. 
typedef struct Term {
	int e;
	int c;
} Term;

// ָ������ֵ������1000������,���ҵݽ�,�����ظ�,����಻����2000����. 
#define MAXN 2005

Term a[MAXN];
 
int main(int argc, char *argv[]) {
	int n=0;
	int k=0;
	int i;
	
	while (scanf("%d%d", &a[n].c, &a[n].e) != EOF) {
		n++;
	}
	
	assert(n<=MAXN);
	for (i=0;i<n;++i) {
		a[i].c *= a[i].e;
		a[i].e--;
		if (a[i].c) {
			a[k++]=a[i];
		}
	}
	
	if (k) {
		for (i=0; i<k;++i) {
			printf("%d %d", a[i].c, a[i].e);
			printf("%s", i==k-1?"\n":" ");
		}
	} else {
		// û�з�������.
		printf("0 0\n"); 
	}
	return 0;
}
