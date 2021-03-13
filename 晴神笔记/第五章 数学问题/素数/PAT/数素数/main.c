#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 要输出第10e4个素数，素数表绝对不止10e4. 
#define MAXN (105000)
int p[MAXN];

int IsPrime(int n) {
	int i;
	int up;
	
	if (n<=1) return 0;
	up=sqrt(n);
	for (i=2;i<=up;++i) {
		if (n % i == 0) return 0;
	}
	return 1;
}

/*
打表发现第10000个素数多大。
*/ 
void FindPrime(void) {
	const int max=1e4;
	int i;
	int k;
	
	for (i=1,k=1;k<=max;++i) {
		if (IsPrime(i)) {
			++k;
		}
	}//104730
	printf("%d\n", i);
}

int main(int argc, char *argv[]) {
	int M,N;
	int i,j;
	int k=0;
	
//	FindPrime();
//	return 0;
	
	scanf("%d%d",&M,&N);
	for (i=2;i<MAXN;++i) {
		if (!p[i]) {
			// 得到一个素数。
			++k;
			
			if (M<=k&&k<=N) {
				printf("%d%s", i, ((k-M+1)%10==0||k==N)?"\n":" ");
			}
			if (k==N) break;
			
			for (j=2*i;j<MAXN;j+=i) {
				p[j]=1;
			}
		}
	}
	
	return 0;
}
