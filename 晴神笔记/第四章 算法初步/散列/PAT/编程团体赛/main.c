#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 1005

int grade[MAXN];

int main(int argc, char *argv[]) {
	int N;
	int i;
	int pos;
	int max;
	
	scanf("%d",&N);
	while (N--) {
		int team, per, gr;
		scanf("%d-%d %d", &team, &per, &gr);
		grade[team] += gr;
	}
	pos=0;
	max=-1;
	for (i=1;i<=1000;++i) {
		if (grade[i] > max) {
			max=grade[i];
			pos=i;
		}
	}
	printf("%d %d\n", pos, max);
	
	return 0;
}
