#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
求第K个素数，则素数表的范围要远大于K的上限。
*/ 
#define MAXN (120000)
int p[MAXN];
int prime[MAXN];
int pNum;

void FindPrime(void) {
	int i,j;
	for (i=2;i<MAXN;++i) {
		if (!p[i]) {
			prime[pNum++]=i;
			for (j=2*i;j<MAXN;j+=i) {
				p[j]=1;
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int K;
	
	FindPrime();
	while (scanf("%d",&K) != EOF) {
		printf("%d\n", prime[K-1]);
	}
	
	return 0;
}
