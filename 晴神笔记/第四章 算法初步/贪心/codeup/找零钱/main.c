#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

const int Face[] = {50, 20, 10, 5, 1};
const int NF = 5;  // 五种面值。

/*
贪心策略，按照面值从大到小考虑，每次尽量取，即n/Fi，
实际上就是把n分解成一种特殊的进制数的各个位。
*/

int main(int argc, char* argv[]) {
    int n;

    freopen("./in.txt", "r", stdin);

    while (scanf("%d", &n) != EOF) {
        int ans[10] = {};  // 每种面值多少张。
        int i;
        int flag = 1;  // 是否为第一个元素。

        for (i = 0; i < 5; ++i) {
            if (n >= Face[i]) {
                ans[i] = n / Face[i];
                n %= Face[i];
            }
        }
        assert(n == 0);

        // 输出结果。
        for (i = 0; i < 5; ++i) {
            if (!ans[i]) continue;
            if (flag) {
                flag = 0;
            } else {
                putchar('+');  // 第一个后面每一个先输出一个加号。
            }
            printf("%d*%d", Face[i], ans[i]);
        }
        putchar('\n');
    }

    return 0;
}
