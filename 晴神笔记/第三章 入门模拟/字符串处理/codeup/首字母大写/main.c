#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 110

int IsSpace(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

int IsLower(char c) {
    return 'a' <= c && c <= 'z';
}

int main(int argc, char* argv[]) {
    char line[MAXN];

    while (gets(line)) {
        int i;
        int len = strlen(line);

        for (i = 0; i < len; ++i) {
            char c = line[i];
            // 识别c是否为首字母，且需要转换。其实 toupper() 即可转换。
            if (IsLower(c) && (i == 0 || IsSpace(line[i - 1]))) {
                putchar('A' + c - 'a');
            } else {
                putchar(c);
            }
        }
        // 注意 gets 会丢弃换行，getline 也会。puts 会添加换行。
        putchar('\n');
    }
    return 0;
}
