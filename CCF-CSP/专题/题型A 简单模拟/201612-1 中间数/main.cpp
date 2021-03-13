#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 1005

int hashtable[MAXN]; // 每个数字的出现次数。
int A[MAXN]; // 不重复的每个数字。
int len;
int N; // 总的输入个数。 
 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	scanf("%d", &N);
	for (int i=0;i<N;++i) {
		int x;
		scanf("%d", &x);
		hashtable[x]++;
		if (hashtable[x] == 1) {
			A[len++]=x;
		}
	}
	sort(A, A+len);
	int less=0; // 小于当前数的个数。
	for (int i=0;i<len;++i) {
		if (2*less + hashtable[A[i]] == N) {
			printf("%d\n", A[i]);
			return 0;	
		}
		less+=hashtable[A[i]];
	}
	printf("-1\n");
	
	return 0;
}
