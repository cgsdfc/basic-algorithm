#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 100

int hashtable[MAXN];
int P[MAXN];

// 生成从1到n的全排列，按字典序从小到大输出。 
void generateP(int index, int n) {
	int i;
	if (index == n+1) {
		for (i=1;i<=n;++i) {
			printf("%d", P[i]);
		}
		printf("\n");
		return;
	}
	for (i=1;i<=n;++i) {
		if (!hashtable[i]) {
			P[index]=i;
			hashtable[i]=1;
			generateP(index + 1, n);
			hashtable[i]=0;
		}
	}
}

int main(int argc, char *argv[]) {
	int n;
	scanf("%d",&n);
	generateP(1, n);
	return 0;
}
