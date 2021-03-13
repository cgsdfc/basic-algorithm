#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 对成绩0-100进行散列。 
#define MAXN 150

int hashtable[MAXN];

int main(int argc, char *argv[]) {
	int N,K;
	int i;
	
	scanf("%d",&N);
	while (N--) {
		int x;
		scanf("%d",&x);
		hashtable[x]++;
	}
	scanf("%d",&K);
	for (i=0;i<K;++i) {
		int x;
		scanf("%d",&x);
		printf("%d%s",hashtable[x],i==K-1?"\n":" ");
	}
	return 0;
}
