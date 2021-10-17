#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, K;  // N个小朋友，K是出局数。

bool Judge(int n) {
    // K的倍数，或者个位数为K。
    return n % K == 0 || n % 10 == K;
}

#define MAXN 1005

// 是否出局。
bool out[MAXN];

int main(int argc, char** argv) {
    scanf("%d%d", &N, &K);
    int i = 1;  // 报数序列。
    int M = N;  // 剩下多少人。
    int next = 0;

    while (M != 1) {
        int k = 0;  // 最多查找N次。
        while (out[next] && k < N) {
            next = (next + 1) % N;
            ++k;
        }
        if (Judge(i)) {
            out[next] = true;
            --M;
        } else {
            next = (next + 1) % N;
        }
        ++i;
    }
    for (int i = 0; i < N; ++i) {
        if (!out[i]) {
            printf("%d\n", i + 1);
            break;
        }
    }
    return 0;
}
