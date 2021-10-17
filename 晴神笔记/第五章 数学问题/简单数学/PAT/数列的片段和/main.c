#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char* argv[]) {
    int i;
    int N;
    long double ans = 0;

    /*
    注意本题要用到long double，并且修饰符为%Lf.
    */
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        long double x;
        scanf("%Lf", &x);
        ans += x * i * (N + 1 - i);
    }
    printf("%.2Lf\n", ans);

    return 0;
}
