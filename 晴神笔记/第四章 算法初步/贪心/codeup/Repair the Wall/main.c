#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef long long LL;
 
#define MAXN 605

int a[MAXN];

int CMP(const void*_a, const void*_b) {
	return *(int*)_b - *(int*)_a; // 从大到小。 
}

int main(int argc, char *argv[]) {
	LL L;
	int N;
	
	while (scanf("%lld%d", &L, &N) != EOF) {
		int i;
		int ans=0; // 多少块。
		 
		for (i=0;i<N;++i) {
			scanf("%d", &a[i]);
		}
		/*
		贪心策略：
		从大到小考虑所有块，选取一块直到填满。
		*/
		qsort(a, N, sizeof(int), CMP);
		for (i=0;i<N;++i) {
			int x=a[i];
			if (L >= 0) {
				/*
				如果L大于等于x，则下一轮继续填补；否则下一轮退出。
				*/ 
				L -= x;
				++ans;
			} else {
				break;
			}
		}
		// 用完了所有块，都无法填补。 
		if (L > 0) {
			puts("impossible");
		} else {
			printf("%d\n", ans);
		}
	}
	
	return 0;
}
