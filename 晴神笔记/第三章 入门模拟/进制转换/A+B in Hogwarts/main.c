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
    //	�ɵ�λ���λ�ۼӡ�
    for (i = MAXN - 1; i >= 0; --i) {
        int s = a[i] + b[i] + cr;
        if (i) {
            c[j] = s % radix[i];
            cr = s / radix[i];
        } else {
            // ���λ����Ҫ��λ��
            c[j] = s;
        }
        j--;
    }
}

void Read(int a[]) {
    scanf("%d.%d.%d", &a[0], &a[1], &a[2]);
}

/*
ע�⣬������������Ϊ10��9�η�����int������ʾ��Χ����˺Ϳ��ܳ���int�ķ�Χ��
������ð���תΪ10���ƣ���ӣ���תΪX���Ƶ��������м������̻������
�����ô������ӷ���д�����򲻻������
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
