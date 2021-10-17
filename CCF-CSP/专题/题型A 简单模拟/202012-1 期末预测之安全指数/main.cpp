#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    int N;
    scanf("%d", &N);
    int ans = 0;
    while (N--) {
        int w, score;
        scanf("%d%d", &w, &score);
        ans += w * score;
    }
    ans = ans > 0 ? ans : 0;
    printf("%d\n", ans);
    return 0;
}
