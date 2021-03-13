#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int N;
	while (scanf("%d", &N) != EOF) {
		int N2=N*N;
		int p=1;
		int ans=0;
		if (N==0) {
			ans=1;
		} else {
			while (N2 / p > 0) {
				p *= 10;
				if (N2 % p == N) {
					ans=1;
					break;
				}
			}
		}
		puts(ans ? "Yes!" : "No!");
	}
	return 0;
}
