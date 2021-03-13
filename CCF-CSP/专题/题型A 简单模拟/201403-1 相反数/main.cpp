#include <cstdio>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 散列。 
#define MAXH 1005

// pos保存每个正数的频数，neg保存每一个负数的频数。 
int pos[MAXH], neg[MAXH];
 
int main(int argc, char** argv) {
	int N;
	scanf("%d", &N);
	while (N--) {
		int x;
		scanf("%d", &x);
		if (x>0) {
			pos[x]++;
		} else {
			neg[-x]++;
		}
	}
	int ans=0;
	for (int i=0;i<MAXH;++i) {
		ans += pos[i]*neg[i];
	}
	printf("%d\n", ans);
	
	return 0;
}
