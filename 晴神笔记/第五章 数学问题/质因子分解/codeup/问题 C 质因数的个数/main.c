#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 100000
int p[MAXN];
int prime[MAXN];
int pNum;

void FindPrime(void) {
	int i;
	int j;
	for (i=2;i<MAXN;++i) {
		if (!p[i]) {
			prime[pNum++]=i;
			for (j=2*i;j<MAXN;j+=i) {
				p[j]=1;
			}
		}
	}
} 

/*
求N的质因数的个数。
*/ 
int Count(int N) {
	int ans=0;
	int i;
	int sqr;
	
	sqr=sqrt(N);
	for (i=0;i<pNum&&prime[i]<=sqr;++i) {
		while (N % prime[i] == 0) {
			++ans;
			N /= prime[i];
		}
	}
	if (N != 1) {
		++ans;
	}
	return ans;
}

int main(int argc, char *argv[]) {
	int N;
	FindPrime();
	while (scanf("%d",&N) != EOF) {
		int ans;
		ans=Count(N);
		printf("%d\n", ans);
	}
	return 0;
}
