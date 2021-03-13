#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 2^15
#define MAXN ((1<<15)+5)

int p[MAXN];

void FindPrime(void) {
	int i;
	int j;
	for (i=2;i<MAXN;++i) {
		if (!p[i]) {
			for (j=i*2;j<MAXN;j+=i) {
				p[j]=1; 
			} 
		}
	}
}


int main(int argc, char *argv[]) {
	int N;
	
	FindPrime();
	while (scanf("%d",&N), N!=0) {
		int ans=0;
		int i;
		int up=N/2;
		for (i=2;i<=up;++i) {
			if (!p[i] && !p[N-i]) {
//				printf("%d %d\n", i, N-i);
				++ans;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

