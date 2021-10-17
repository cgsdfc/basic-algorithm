#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char* argv[]) {
    int x;  // 先读第一个数试探。
    while (scanf("%d", &x) != EOF) {
        int i;
        int count[20] = {};
        int pos;
        int max = -1;

        count[x]++;
        for (i = 1; i < 20; i++) {
            scanf("%d", &x);
            count[x]++;
        }
        for (i = 1; i <= 10; ++i) {
            if (count[i] > max) {
                max = count[i];
                pos = i;
            }
        }
        printf("%d\n", pos);
    }
    return 0;
}
