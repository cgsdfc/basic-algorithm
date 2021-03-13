#include <cstdio>

#define MAXN 1005

int count[MAXN];

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int N;
	scanf("%d", &N);
	while (N--) {
		int x;
		scanf("%d", &x);
		++count[x];
		printf("%d%s", count[x], N?" ":"\n");
	}
	return 0;
}
