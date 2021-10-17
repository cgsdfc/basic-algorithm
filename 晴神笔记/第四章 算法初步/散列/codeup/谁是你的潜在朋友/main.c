#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 最大读者/书数是200
#define MAXN 210

// 第i个读者喜欢哪本书。
int reader[MAXN];

// 每本书有多少共同读者。
// 当共同读者数是1时，表示没有朋友，否则有N-1个朋友。
int book[MAXN];

int main(int argc, char* argv[]) {
    int N, M;

    while (scanf("%d%d", &N, &M) != EOF) {
        int i;
        memset(book, 0, sizeof(book));
        memset(reader, 0, sizeof(book));

        for (i = 1; i <= N; ++i) {
            int b;
            // 读者i喜欢书b。
            scanf("%d", &b);
            reader[i] = b;
            // 注意！多点测试要把变量归零。
            book[b]++;
        }
        for (i = 1; i <= N; ++i) {
            int b = reader[i];
            int bs = book[b];
            if (bs > 1) {
                printf("%d\n", bs - 1);
            } else if (bs == 1) {
                puts("BeiJu");
            }
        }
    }
    return 0;
}
