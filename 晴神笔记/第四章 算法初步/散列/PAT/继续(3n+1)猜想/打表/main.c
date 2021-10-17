#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char* argv[]) {
    int max = -1;
    int i;
    int pos;

    for (i = 1; i <= 100; ++i) {
        int x = i;
        while (x != 1) {
            if (x % 2) {
                x = (3 * x + 1) / 2;
            } else {
                x /= 2;
            }
            if (x > max) {
                max = x;
                pos = i;
            }
        }
    }
    printf("%d %d\n", pos, max);

    return 0;
}
