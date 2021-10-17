#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXD 1005
typedef struct Big {
    int d[MAXD];
    int len;
} Big;

/*
其实直接strcmp，字典序比较字符串就可以了。
*/
int CMP(const void* _a, const void* _b) {
    Big* a = _a;
    Big* b = _b;
    int i;

    if (a->len != b->len) { return a->len - b->len; }
    // 按从高到低存放。
    for (i = 0; i < a->len; ++i) {
        if (a->d[i] != b->d[i]) { return a->d[i] - b->d[i]; }
    }
    return 0;
}

#define MAXN 101

Big a[MAXN];
char str[MAXD];

int main(int argc, char* argv[]) {
    int N;
    while (scanf("%d", &N) != EOF) {
        int i;
        int j;
        for (i = 0; i < N; ++i) {
            int len;
            scanf("%s", str);
            a[i].len = len = strlen(str);
            for (j = 0; j < len; ++j) {
                a[i].d[j] = str[j] - '0';
            }
        }
        qsort(a, N, sizeof(a[0]), CMP);
        for (i = 0; i < N; ++i) {
            for (j = 0; j < a[i].len; ++j) {
                printf("%d", a[i].d[j]);
            }
            printf("\n");
        }
    }
    return 0;
}
