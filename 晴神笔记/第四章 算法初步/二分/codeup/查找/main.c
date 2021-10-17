#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 110

int a[MAXN];

int main(int argc, char* argv[]) {
    int n;

    while (scanf("%d", &n) != EOF) {
        int i;
        int m;

        for (i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        scanf("%d", &m);
        while (m--) {
            int x;
            scanf("%d", &x);
            for (i = 0; i < n; ++i) {
                if (a[i] == x) {
                    puts("YES");
                    break;
                }
            }
            if (i == n) { puts("NO"); }
        }
    }
    return 0;
}
