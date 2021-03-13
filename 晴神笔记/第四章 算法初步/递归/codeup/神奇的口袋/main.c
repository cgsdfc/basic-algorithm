#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
// 物品的数量 
#define MAXN (20+5)
// 物品体积的最大值 
#define MAXM (40+5)

int a[MAXN];
int hashtable[MAXM];

// 方法的总数。 
int sum=0;

/*
V是物品当前体积，
n是物品数量。
枚举N个元素的集合的所有子集，共2^n个。
题目保证各个物品体积不同。 
*/ 
int Find(int V, int N, int curval) {
	if (N == 0) {
		if (curval == V) {
			++sum;
		}
		return;
	}
	// 当前元素a[N-1] 
	if (curval > V) {
		// 剪枝，就算后面的元素都不取，也不可能满足。 
		return;
	}
	
	// 不取当前元素 。
	Find(V, N-1, curval);
	// 取当前元素。 
	Find(V, N-1, curval+a[N-1]);
}

int main(int argc, char *argv[]) {
	int n;
	int i;
	
//	freopen("./in.txt","r",stdin);
	
	while (scanf("%d", &n) != EOF) {
		memset(hashtable, 0, sizeof(hashtable));
		for (i=0;i<n;++i) {
			scanf("%d",&a[i]);
			hashtable[a[i]]++;
		}
		sum=0;
		Find(40, n, 0);
		printf("%d\n", sum);
	}
	return 0;
}
