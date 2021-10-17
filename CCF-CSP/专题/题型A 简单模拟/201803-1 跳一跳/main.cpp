#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    int ans = 0;    // 总分。
    int last = -1;  // 上次得分。

    int x;
    while (scanf("%d", &x), x) {
        int now;  // 本轮得分。
        if (x == 1) {
            now = 1;
        } else {
            if (last == -1 || last == 1) {
                now = 2;
            } else {
                now = last + 2;
            }
        }
        ans += now;
        last = now;
    }
    printf("%d\n", ans);

    return 0;
}
