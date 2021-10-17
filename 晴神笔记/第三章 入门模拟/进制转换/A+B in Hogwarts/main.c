#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct Money {
    int g, s, k;
} Money;

#define MAXN 3

const int radix[] = {0, 17, 29};

void Add(int a[], int b[], int c[]) {
    int i;
    int j;
    int cr = 0;

    j = MAXN - 1;
    //	由低位向高位累加。
    for (i = MAXN - 1; i >= 0; --i) {
        int s = a[i] + b[i] + cr;
        if (i) {
            c[j] = s % radix[i];
            cr = s / radix[i];
        } else {
            // 最高位不需要进位。
            c[j] = s;
        }
        j--;
    }
}

void Read(int a[]) {
    scanf("%d.%d.%d", &a[0], &a[1], &a[2]);
}

/*
注意，本题两个加数为10的9次方，即int的最大表示范围，因此和可能超过int的范围，
如果采用把数转为10进制，相加，再转为X进制的做法，中间计算过程会溢出。
而采用大整数加法的写法，则不会溢出。
*/
int main(int argc, char* argv[]) {
    int a[MAXN], b[MAXN], c[MAXN];
    int i;

    Read(a);
    Read(b);
    Add(a, b, c);
    for (i = 0; i < MAXN; ++i) {
        printf("%d%s", c[i], i == MAXN - 1 ? "\n" : ".");
    }

    return 0;
}
