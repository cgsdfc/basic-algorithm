#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char* argv[]) {
    int n;
    while (scanf("%d", &n) != EOF) {
        while (n--) {
            int a;
            scanf("%d", &a);
            if (a & 1) {
                // odd
                puts("0 0");
                continue;
            }
            /*
            最大值：令2尽量多。
            最小值：令4尽量多。
            */
            if (a % 4 == 0) {
                // 最小值，最大值。
                printf("%d %d\n", a / 4, a / 2);
            } else {
                /*
                注意，2的倍数而非4的倍数，模4，得出一定是2.
                说明最后一个动物必须有2腿。
                */
                printf("%d %d\n", a / 4 + 1, a / 2);
            }
        }
    }
    return 0;
}
