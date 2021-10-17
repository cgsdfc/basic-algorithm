#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int N;  // 报数的总数。

// 跳过的规则。
bool Judge(int a) {
    if (a % 7 == 0) return true;
    while (a) {
        if (a % 10 == 7) return true;
        a /= 10;
    }
    return false;
}

int ans[4];

int main(int argc, char** argv) {
    scanf("%d", &N);

    int i = 1;  // 计数当前的数。
    int j = 0;  // 当前的有效计数。
    while (j < N) {
        int now = (i - 1) % 4;  // 当前报数的人。
        if (Judge(i)) {
            // 跳过。
            ++ans[now];
        } else {
            ++j;
        }
        ++i;
    }
    for (int i = 0; i < 4; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
