#include <cstdio>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int N, K; // n����������kÿһ����С�ĵ������� 

int main(int argc, char** argv) {
	scanf("%d%d", &N, &K);
	int ans=0;
	int i=0;
	while (i<N) {
		int now=0; // ��ǰ���ѷ��˶��١�
		while (now<K && i<N) {
			int x;
			scanf("%d", &x);
//			printf("%d\n", x);
			now += x;
			++i;
		}
		++ans;
//		printf("\n");
	}
	printf("%d\n", ans);
	
	return 0;
}
