#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
给定N个整数（有些带前导零），问如何排列它们使得连在一起所得的整数最小。
本题的贪心策略是：任意两个整数a，b，它们对应的字符串也记作a，b，如果a+b < b+a
（字符串的连接操作），则a在整个序列中应该排在b的前面。也就是定义了一种序，按这种序对
N个字符串排序，即可。
*/

#define MAXS 10
#define MAXM (2 * MAXS)
#define MAXN 10005

typedef struct Node Node;
struct Node {
    char str[MAXS];
};

void StrCat(char a[], char b[], char c[]) {
    while (*a) {
        *c++ = *a++;
    }
    while (*b) {
        *c++ = *b++;
    }
    *c = 0;
}

int CMP(const void* _a, const void* _b) {
    Node* a = (Node*) _a;
    Node* b = (Node*) _b;
    char ab[MAXM];
    char ba[MAXM];

    StrCat(a->str, b->str, ab);
    StrCat(b->str, a->str, ba);
    return strcmp(ab, ba);
}

Node nodes[MAXN];

int main(int argc, char* argv[]) {
    int N;
    int i;
    int sum = 0;
    int flag;

    scanf("%d", &N);
    for (i = 0; i < N; ++i) {
        scanf("%s", nodes[i].str);
    }
    qsort(nodes, N, sizeof(Node), CMP);

    /*
    注意去掉前导零的逻辑，不要变成去掉所有0.
    */
    flag = 1;
    for (i = 0; i < N; ++i) {
        int j;
        int len;
        for (j = 0, len = strlen(nodes[i].str); j < len; ++j) {
            char c = nodes[i].str[j];
            if (c == '0' && flag) continue;
            // 遇到第一个非零数，则把flag改了。
            flag = 0;
            putchar(c);
            ++sum;
        }
    }
    // 如果全部是0，则应该输出单0.
    if (!sum) { putchar('0'); }
    putchar('\n');
    return 0;
}
