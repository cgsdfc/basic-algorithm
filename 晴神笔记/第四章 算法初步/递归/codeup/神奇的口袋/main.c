#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
// ��Ʒ������ 
#define MAXN (20+5)
// ��Ʒ��������ֵ 
#define MAXM (40+5)

int a[MAXN];
int hashtable[MAXM];

// ������������ 
int sum=0;

/*
V����Ʒ��ǰ�����
n����Ʒ������
ö��N��Ԫ�صļ��ϵ������Ӽ�����2^n����
��Ŀ��֤������Ʒ�����ͬ�� 
*/ 
int Find(int V, int N, int curval) {
	if (N == 0) {
		if (curval == V) {
			++sum;
		}
		return;
	}
	// ��ǰԪ��a[N-1] 
	if (curval > V) {
		// ��֦����������Ԫ�ض���ȡ��Ҳ���������㡣 
		return;
	}
	
	// ��ȡ��ǰԪ�� ��
	Find(V, N-1, curval);
	// ȡ��ǰԪ�ء� 
	Find(V, N-1, curval+a[N-1]);
}

int main(int argc, char *argv[]) {
	int n;
	int i;
	
//	freopen("./in.txt","r",stdin);
	
	while (scanf("%d", &n) != EOF) {
		memset(hashtable, 0, sizeof(hashtable));
		for (i=0;i<n;++i) {
			scanf("%d",&a[i]);
			hashtable[a[i]]++;
		}
		sum=0;
		Find(40, n, 0);
		printf("%d\n", sum);
	}
	return 0;
}
