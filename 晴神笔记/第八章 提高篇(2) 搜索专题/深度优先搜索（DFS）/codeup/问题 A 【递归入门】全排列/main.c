#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 20
/*
注意到，打印全排列的递归算法，栈最大深度为N，辅助空间也是O(N)，
但是时间是N！，所以，为了算法在有限时间内运行完，N不可能很大，
所以递归算法是完全可行的，不存在爆栈。
*/

int hashtable[MAXN]; // 指示第i个元素是否已使用。 
int ans[MAXN]; // 存放生成的排列。
int N;

// index 考虑的第i个位置，控制算法结束。 
void DFS(int index) {
	int i;
	if (index == N) {
		for (i=0;i<N;++i) {
			printf("%d%s", ans[i], i==N-1?"\n":" ");
		}
		return;
	}
	for (i=1;i<=N;++i) {
		if (!hashtable[i]) {
			hashtable[i]=1;
			ans[index]=i;
			DFS(index+1);
			hashtable[i]=0;
		}
	}
}

int main(int argc, char *argv[]) {
	while (scanf("%d", &N) != EOF) {
		DFS(0);
	}
	return 0;
}

