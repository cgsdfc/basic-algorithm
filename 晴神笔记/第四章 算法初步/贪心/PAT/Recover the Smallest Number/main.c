#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
����N����������Щ��ǰ���㣩���������������ʹ������һ�����õ�������С��
�����̰�Ĳ����ǣ�������������a��b�����Ƕ�Ӧ���ַ���Ҳ����a��b�����a+b < b+a
���ַ��������Ӳ���������a������������Ӧ������b��ǰ�档Ҳ���Ƕ�����һ���򣬰��������
N���ַ������򣬼��ɡ�
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
    ע��ȥ��ǰ������߼�����Ҫ���ȥ������0.
    */
    flag = 1;
    for (i = 0; i < N; ++i) {
        int j;
        int len;
        for (j = 0, len = strlen(nodes[i].str); j < len; ++j) {
            char c = nodes[i].str[j];
            if (c == '0' && flag) continue;
            // ������һ�������������flag���ˡ�
            flag = 0;
            putchar(c);
            ++sum;
        }
    }
    // ���ȫ����0����Ӧ�������0.
    if (!sum) { putchar('0'); }
    putchar('\n');
    return 0;
}
