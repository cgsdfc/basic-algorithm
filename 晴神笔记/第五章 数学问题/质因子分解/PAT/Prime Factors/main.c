#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct Factor {
	int x;
	int cnt;
} Factor;

Factor F[10];

// 打素数表 
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

int main(int argc, char *argv[]) {
	int N;
	int num=0;
	int i;
	int sqr;
	int N2;
	
	FindPrime();	
	scanf("%d", &N);
	/*
	注意，N=1，1没有质因数，但是要输出1=1，
	否则第二个点不过。
	*/
	if (N==1) {
		printf("1=1\n");
		return 0;
	}
	
	N2=N;
	sqr=sqrt(N);
	for (i=0;i<pNum&&prime[i]<=sqr;++i) {
		int p=prime[i];
		if (N % p == 0) {
			F[num].x=p;
			F[num].cnt=0;
			while (N % p == 0) {
				F[num].cnt++;
				N /= p;
			}
			++num;
		}
	}
	if (N != 1) {
		F[num].x=N;
		F[num].cnt=1;
		++num;
	}
	printf("%d=", N2);
	 
	for (i=0;i<num;++i) {
		printf("%d", F[i].x);
		if (F[i].cnt != 1) {
			printf("^%d", F[i].cnt);
		}
		printf("%s", i==num-1?"\n":"*");
	}
	
	return 0;
}
