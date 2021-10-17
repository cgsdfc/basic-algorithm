#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char* argv[]) {
    int n, i = 0;

    scanf("%d", &n);
    while (n != 1) {
        if (n % 2 == 1) {
            n = (3 * n + 1) / 2;
        } else {
            n /= 2;
        }
        ++i;
    }
    printf("%d\n", i);
    return 0;
}
