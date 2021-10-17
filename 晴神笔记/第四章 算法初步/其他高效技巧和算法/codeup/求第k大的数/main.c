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
注意区分“第K大”和“第K小”。
书说的“第K大”，实际上是第K小。
所谓第K小，是指序列中有K-1个数小于等于它。
所谓第K大，是指序列中有K-1个数大于等于它。
最小值，就是第1小，第N大；
最大值，就是第1大，第N小。

本题说的第K大，就是真正意义上的，不是书本上的第K小。
二者有转换公式：
第K大==第N-K+1小。
第K小==第N-K+1大。

另外：K一般从1开始。
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
