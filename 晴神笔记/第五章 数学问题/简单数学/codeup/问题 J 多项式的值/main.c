#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 20
int a[MAXN];

int main(int argc, char *argv[]) {
	int m;
	while (scanf("%d",&m) != EOF) {
		while (m--) {
			int n;
			int i;
			int x;
			int ans=0;
			
			scanf("%d", &n);
			for (i=0;i<=n;++i) {
				// n+1
				scanf("%d", &a[i]);
			}
			
//			for (i=0;i<=n;++i) {
//				printf("%d%s", a[i], i==n?"\n":" ");
//			}
//			
			scanf("%d", &x);
			for (i=n;i>=0;--i) {
				ans=ans*x+a[i];
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
