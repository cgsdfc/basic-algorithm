#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 256
#define MAXS 1010

int hashtable[MAXN];
char sell[MAXS], want[MAXS];

/*
������ʵ�������������ؼ�A��B�����⣬�������£�
��A�Ƿ�ΪB���Ӽ������ǣ������|B-A|�������ǣ�
�����|A-B|�����仰˵��
�� A��B���Ӽ��������B�ж�Aû�е�Ԫ�أ���A����B���Ӽ���
�����A�ж�Bû�е�Ԫ�ء�
��ν�ġ��������������B��A���Ԫ�أ���ν�ĵġ�������١�������
A�ж�Bû�е�Ԫ�ء�
*/

// ���ؼ��������ʾ��ÿһ������Ԫ��a[i]��ʾ����Ԫ��i ��������
// ����a�Ƿ�Ϊb���Ӽ���
int SubSet(int a[], int b[]) {
    int i;
    for (i = 0; i < MAXN; ++i) {
        if (a[i] > b[i]) return 0;
    }
    return 1;
}

// ����C=A-B��
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
            // ��������
            rest += x;
        } else {
            // ����Ӧ��
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
