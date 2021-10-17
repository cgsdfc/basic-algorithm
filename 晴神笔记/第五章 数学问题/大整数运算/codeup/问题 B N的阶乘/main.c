#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
N�Ľ׳��ж���λ��
��N^N�����ƣ���N��1000����ôN^N����3000λ������N�Ľ׳�С�ڵ���3000λ��
*/

#define MAXN 3000
typedef struct Big {
    int d[MAXN];
    int len;
} Big;

Big ans;

// ans *= b;
void Mult(int b) {
    int i;
    int len = 0;
    int carry = 0;

    for (i = 0; i < ans.len; ++i) {
        int temp = ans.d[i] * b + carry;
        ans.d[len++] = temp % 10;
        carry = temp / 10;
    }
    while (carry != 0) {
        ans.d[len++] = carry % 10;
        carry /= 10;
    }
    ans.len = len;
}

// ��ӡ�м���
void Print(void) {
    int i;
    for (i = ans.len - 1; i >= 0; --i) {
        printf("%d", ans.d[i]);
    }
    printf("\n");
}

void Factoral(int N) {
    int i;
    if (N == 0 || N == 1) {
        printf("1\n");
        return;
    }
    // ans=1
    ans.d[0] = 1;
    ans.len = 1;
    for (i = 2; i <= N; ++i) {
        Mult(i);
        //		Print();
    }
    Print();
}

int main(int argc, char* argv[]) {
    int N;
    while (scanf("%d", &N) != EOF) {
        Factoral(N);
    }

    return 0;
}
