#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    int r, y, g;
    int n;
    scanf("%d%d%d", &r, &y, &g);
    scanf("%d", &n);
    int ans = 0;
    while (n--) {
        int k, t;
        scanf("%d%d", &k, &t);
        if (k == 0) {
            ans += t;
        } else if (k == 1) {
            // Red
            ans += t;
        } else if (k == 2) {
            // Yellow
            ans += t + r;  // 先等黄灯，再等红灯。
        }
    }
    printf("%d\n", ans);

    return 0;
}
