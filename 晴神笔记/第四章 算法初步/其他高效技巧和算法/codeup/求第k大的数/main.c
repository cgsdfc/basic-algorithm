#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1000005

int a[MAXN];

int Partition(int a[], int L, int R) {
    int temp;

    temp = a[L];
    while (L < R) {
        while (L < R && a[R] > temp)
            --R;
        a[L] = a[R];
        while (L < R && a[L] <= temp)
            ++L;
        a[R] = a[L];
    }
    a[L] = temp;
    return L;
}

int Select(int a[], int L, int R, int K) {
    int p;
    int M;

    if (L == R) return a[L];
    p = Partition(a, L, R);
    M = p - L + 1;
    if (M == K) return a[p];
    if (K < M) {
        return Select(a, L, p - 1, K);
    } else {
        return Select(a, p + 1, R, K - M);
    }
}

/*
ע�����֡���K�󡱺͡���KС����
��˵�ġ���K�󡱣�ʵ�����ǵ�KС��
��ν��KС����ָ��������K-1����С�ڵ�������
��ν��K����ָ��������K-1�������ڵ�������
��Сֵ�����ǵ�1С����N��
���ֵ�����ǵ�1�󣬵�NС��

����˵�ĵ�K�󣬾������������ϵģ������鱾�ϵĵ�KС��
������ת����ʽ��
��K��==��N-K+1С��
��KС==��N-K+1��

���⣺Kһ���1��ʼ��
*/

int main(int argc, char* argv[]) {
    int N, K;

    //	while (scanf("%d%d", &N, &K) != EOF) {

    int i;
    int ans;

    scanf("%d%d", &N, &K);

    for (i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
    }
    ans = Select(a, 0, N - 1, N - K + 1);
    printf("%d\n", ans);
    //	}
    return 0;
}
