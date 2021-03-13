#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define MAXN 1000
int E[MAXN], G[MAXN];
int numE, numG;

int Judge(int N) {
	int sum=0;
	int sqr;
	int i;
	
	if (N==1) {
		return 0;
	}
	sqr=sqrt(N);
	for (i=1;i<=sqr;++i) {
		if (N % i == 0) {
			sum+=i;
			if (i!=1 && i*i!=N) {
				sum+=N/i;
			}
		}
	}
	if (sum == N) return 1; // ÍêÊý
	if (sum > N) return 2; // Ó¯Êý
	return 0; 
}

int main(int argc, char *argv[]) {
	int i;
	for (i=2;i<=60;++i) {
		switch (Judge(i)) {
			case 1:
				E[numE++]=i;
				break;
			case 2:
				G[numG++]=i;
				break;
		}
	}
	printf("E:");
	for (i=0;i<numE;++i) {
		printf(" %d", E[i]);
	}
	printf("\n");
	printf("G:");
	for (i=0;i<numG;++i) {
		printf(" %d", G[i]);
	}
	printf("\n");
	return 0;
}
