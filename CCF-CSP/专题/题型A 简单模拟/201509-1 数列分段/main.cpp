#include <cstdio>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int N;
	scanf("%d", &N);
	int ans=0;
	int now;
	for (int i=0;i<N;++i) {
		int x;
		scanf("%d", &x);
		if (i==0) {
			now=x;
			ans=1;
		} else {
			if (x != now) {
				++ans;
				now=x;
			}
		}
	}
	printf("%d\n", ans);
	
	return 0;
}
