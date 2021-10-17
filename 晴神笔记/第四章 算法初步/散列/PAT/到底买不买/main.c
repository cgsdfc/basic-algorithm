#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 256
#define MAXS 1010

int hashtable[MAXN];
char sell[MAXS], want[MAXS];

/*
此问题实际上是两个多重集A，B的问题，翻译如下：
问A是否为B的子集，若是，则输出|B-A|，若不是，
则输出|A-B|。换句话说，
若 A是B的子集，则输出B有而A没有的元素，若A不是B的子集，
则输出A有而B没有的元素。
所谓的“多出来”，就是B比A多的元素；所谓的的“还差多少”，就是
A有而B没有的元素。
*/

// 多重集用数组表示，每一个数组元素a[i]表示集合元素i 的重数。
// 计算a是否为b的子集。
int SubSet(int a[], int b[]) {
    int i;
    for (i = 0; i < MAXN; ++i) {
        if (a[i] > b[i]) return 0;
    }
    return 1;
}

// 计算差集C=A-B。
int Sub(int a[], int b[], int c[]) {
    int i;
    for (i = 0; i < MAXN; ++i) {
        if (a[i] > b[i]) { c[i] = a[i] - b[i]; }
    }
}

void Init(int set[], char str[]) {
    int i;
    int len;

    memset(set, 0, sizeof(int) * MAXN);
    for (i = 0, len = strlen(str); i < len; ++i) {
        set[str[i]]++;
    }
}

int Size(int set[]) {
    int size = 0;
    int i;
    for (i = 0; i < MAXN; ++i) {
        size += set[i];
    }
    return size;
}

int A[MAXN], B[MAXN], C[MAXN];

void Solve(char sell[], char want[]) {
    Init(A, sell);
    Init(B, want);
    if (SubSet(B, A)) {
        Sub(A, B, C);
        printf("Yes ");
    } else {
        Sub(B, A, C);
        printf("No ");
    }
    printf("%d\n", Size(C));
}

int main(int argc, char* argv[]) {
    int i;
    int rest, lack;
    int len1, len2;

    gets(sell);
    gets(want);

    Solve(sell, want);
    return 0;

    for (i = 0, len1 = strlen(want); i < len1; ++i) {
        hashtable[want[i]]--;
    }
    for (i = 0, len2 = strlen(sell); i < len2; ++i) {
        hashtable[sell[i]]++;
    }
    rest = lack = 0;
    for (i = 0; i < MAXN; ++i) {
        int x = hashtable[i];
        if (x > 0) {
            // 供大于求。
            rest += x;
        } else {
            // 供不应求。
            lack -= x;
        }
    }

    if (lack == 0) {
        printf("Yes %d\n", rest);
    } else {
        printf("No %d\n", lack);
    }
    return 0;
}
