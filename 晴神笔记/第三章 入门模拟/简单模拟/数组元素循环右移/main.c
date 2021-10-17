#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

void Move(int a[], int n, int m) {
    int i;
    int j = 0;

    m = m % n;
    for (i = n - m; i < n; ++i, ++j) {
        printf("%d", a[i]);
        printf("%s", j == n - 1 ? "\n" : " ");
    }
    for (i = 0; i < n - m; ++i, ++j) {
        printf("%d", a[i]);
        printf("%s", j == n - 1 ? "\n" : " ");
    }
}

int main(int argc, char* argv[]) {
    int n, m;
    int a[105];
    int i;

    scanf("%d%d", &n, &m);
    for (i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    Move(a, n, m);

    return 0;
}
