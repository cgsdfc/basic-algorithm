#include <cstdio>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int N, K; // n蛋糕总数，k每一个最小的蛋糕量。 

int main(int argc, char** argv) {
	scanf("%d%d", &N, &K);
	int ans=0;
	int i=0;
	while (i<N) {
		int now=0; // 当前朋友分了多少。
		while (now<K && i<N) {
			int x;
			scanf("%d", &x);
//			printf("%d\n", x);
			now += x;
			++i;
		}
		++ans;
//		printf("\n");
	}
	printf("%d\n", ans);
	
	return 0;
}
