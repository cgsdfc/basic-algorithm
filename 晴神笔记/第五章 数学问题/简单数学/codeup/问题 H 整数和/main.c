#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char* argv[]) {
    int M, N;
    while (scanf("%d", &M) != EOF) {
        while (M--) {
            int ans;
            scanf("%d", &N);
            ans = 3 * N * (abs(N) + 1) / 2;
            printf("%d\n", ans);
        }
    }
    return 0;
}
