#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef long long LL;
 
#define MAXN 605

int a[MAXN];

int CMP(const void*_a, const void*_b) {
	return *(int*)_b - *(int*)_a; // �Ӵ�С�� 
}

int main(int argc, char *argv[]) {
	LL L;
	int N;
	
	while (scanf("%lld%d", &L, &N) != EOF) {
		int i;
		int ans=0; // ���ٿ顣
		 
		for (i=0;i<N;++i) {
			scanf("%d", &a[i]);
		}
		/*
		̰�Ĳ��ԣ�
		�Ӵ�С�������п飬ѡȡһ��ֱ��������
		*/
		qsort(a, N, sizeof(int), CMP);
		for (i=0;i<N;++i) {
			int x=a[i];
			if (L >= 0) {
				/*
				���L���ڵ���x������һ�ּ������������һ���˳���
				*/ 
				L -= x;
				++ans;
			} else {
				break;
			}
		}
		// ���������п飬���޷���� 
		if (L > 0) {
			puts("impossible");
		} else {
			printf("%d\n", ans);
		}
	}
	
	return 0;
}
