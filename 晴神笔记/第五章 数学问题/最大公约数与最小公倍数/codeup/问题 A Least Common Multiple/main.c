#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
N个数的最小公倍数lcm
计算两个数的lcm，这个结果再和第三个计算lcm，等等。
lcm(a0, lcm(a1, a2))
*/

int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    int d = gcd(a, b);
    return a / d * b;
}

int main(int argc, char* argv[]) {
    int N;
    while (scanf("%d", &N) != EOF) {
        while (N--) {
            int m;
            int ans;
            int i;

            scanf("%d", &m);
            assert(m > 0);
            scanf("%d", &ans);
            for (i = 1; i < m; ++i) {
                int x;
                scanf("%d", &x);
                ans = lcm(ans, x);
            }
            printf("%d\n", ans);
        }
    }

    return 0;
}
