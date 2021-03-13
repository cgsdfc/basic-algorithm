#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int Count(int N) {
	int i;
	int sqr;
	int ans=0;
	
	sqr=sqrt(N);
	for (i=1;i<=sqr;++i) {
		if (N % i == 0) {
			++ans;
			if (N/i != i) {
				++ans;
			}
		}
	}
	return ans;
}

int main(int argc, char *argv[]) {
	int N;
	while (scanf("%d",&N) != EOF && N != 0) {
		while (N--) {
			int X;
			scanf("%d", &X);
			printf("%d\n", Count(X));
		}
	}
	return 0;
}
