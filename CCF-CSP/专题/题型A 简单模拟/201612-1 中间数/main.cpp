#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 1005

int hashtable[MAXN]; // ÿ�����ֵĳ��ִ�����
int A[MAXN]; // ���ظ���ÿ�����֡�
int len;
int N; // �ܵ���������� 
 
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
	int less=0; // С�ڵ�ǰ���ĸ�����
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
