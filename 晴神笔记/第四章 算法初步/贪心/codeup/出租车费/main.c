#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
直接模拟贪心策略如下：
1. 先处理边界情况。
2. 开始坐车，当前大于6公里，则换车，然后坐车直到第三阶段，或者到达。
3. 当前小于6公里，不换车直到到达。
*/
double Cost(int n) {
    double ans;
    if (n <= 4) return 10;
    if (n <= 8) return 10 + 2 * (n - 4);
    // 前两阶段结束。
    ans = 18;
    n -= 8;
    assert(n > 0);
    while (n > 0) {
        if (n >= 6) {
            // 做6公里以上的车，则换车后更便宜。
            if (n <= 8) {
                // 直接到达了。
                ans += 10 + (n - 4) * 2;
                break;
            } else {
                ans += 18;
                n -= 8;
            }
        } else {
            // 不足6公里了，换车不能更便宜。
            ans += n * 2.4;
            break;
        }
    }
    return ans;
}

/*
更快的实现。
首先每8公里换车一次，即每次走完第一第二阶段（8公里）就换车。
这是因为：
1. 第一个8公里必须走完。
2. 走完第一个8公里后，如果剩下的大于8公里，则换车比继续坐车便宜（18 vs 19.2）。
当剩下的公里不足8时，因为公里数==5时，换车和继续坐车恰好相等，所以
1. n小于5时，继续坐车。
2. n大于等于5时，换车。
*/
double Cost2(int n) {
    double ans;

    if (n <= 4) return 10;
    if (n <= 8) return 10 + 2 * (n - 4);
    // 可以从0开始，因为这样包括了首个8公里。
    ans = 0;
    while (n >= 8) {
        ans += 18;
        n -= 8;
    }
    if (n < 5) {
        ans += n * 2.4;
    } else {
        ans += 10 + (n - 4) * 2;
    }
    return ans;
}

int main(int argc, char* argv[]) {
    int n;

    freopen("./in.txt", "r", stdin);

    while (scanf("%d", &n), n != 0) {
        double ans = Cost2(n);
        if ((int) ans == ans) {
            printf("%d\n", (int) ans);
        } else {
            printf("%.1f\n", ans);
        }
    }
    return 0;
}
