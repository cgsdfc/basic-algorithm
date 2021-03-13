#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 20
/*
ע�⵽����ӡȫ���еĵݹ��㷨��ջ������ΪN�������ռ�Ҳ��O(N)��
����ʱ����N�������ԣ�Ϊ���㷨������ʱ���������꣬N�����ܴܺ�
���Եݹ��㷨����ȫ���еģ������ڱ�ջ��
*/

int hashtable[MAXN]; // ָʾ��i��Ԫ���Ƿ���ʹ�á� 
int ans[MAXN]; // ������ɵ����С�
int N;

// index ���ǵĵ�i��λ�ã������㷨������ 
void DFS(int index) {
	int i;
	if (index == N) {
		for (i=0;i<N;++i) {
			printf("%d%s", ans[i], i==N-1?"\n":" ");
		}
		return;
	}
	for (i=1;i<=N;++i) {
		if (!hashtable[i]) {
			hashtable[i]=1;
			ans[index]=i;
			DFS(index+1);
			hashtable[i]=0;
		}
	}
}

int main(int argc, char *argv[]) {
	while (scanf("%d", &N) != EOF) {
		DFS(0);
	}
	return 0;
}

