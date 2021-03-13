#include <cstdio>
#include <algorithm>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int N;

int main(int argc, char** argv) {
	scanf("%d", &N);
	int pre;
	int ans=-1;
	
	// 检查每一个数和它的前驱的查找即可。 
	for (int i=0;i<N;++i) {
		int now;
		scanf("%d", &now);
		if (i>0) {
			int diff=abs(now-pre);
			ans=max(ans, diff);
		}
		pre=now;
	}
	printf("%d\n", ans);
	
	return 0;
}
