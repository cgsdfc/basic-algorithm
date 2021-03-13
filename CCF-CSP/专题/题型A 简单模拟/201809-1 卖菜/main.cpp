#include <cstdio>

#define MAXN 1005

int now[MAXN]; // 第一天菜价。
int N;
 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	scanf("%d", &N);
	for (int i=0;i<N;++i) {
		scanf("%d", &now[i]);
	}
	for (int i=0;i<N;++i) {
		int x=now[i];
		int n=1;
		if (i>0) {
			x+=now[i-1];
			++n;
		}
		if (i<N-1) {
			x+=now[i+1];
			++n;
		}
		printf("%d%s", x/n, i==N-1?"\n":" ");
	}
	
	return 0;
}
