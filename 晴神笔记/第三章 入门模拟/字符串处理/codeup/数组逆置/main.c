#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 210

int main(int argc, char* argv[]) {
    char str[MAXN];

    while (gets(str)) {
        int i;
        int len = strlen(str);
        // reverse 模板，也可以用 std::reverse
        for (i = 0; i < len / 2; ++i) {
            char tmp = str[i];
            str[i] = str[len - 1 - i]; // i的对称位置
            str[len - 1 - i] = tmp;
        }
        puts(str);
    }
    return 0;
}
