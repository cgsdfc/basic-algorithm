#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 1005

int a[MAXN];
int N;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
����Ȼ����������ֻ������x��x�ĺ���в�����
*/
 
int main(int argc, char** argv) {
	scanf("%d", &N);
	for (int i=0;i<N;++i) {
		scanf("%d", &a[i]);
	}
	sort(a, a+N);
	int ans=0;
	for (int i=1;i<N;++i) {
		// ��x��x��ǰ����
		if (a[i]-a[i-1]==1) {
			++ans;
		} 
	}
	printf("%d\n", ans);
	return 0;
}
