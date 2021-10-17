#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN (100000 + 1)

// int p[MAXN];
/*
�������ݹ�ģ��һ����ѯ�����2*sqrt(10e5)����1000���ҡ�
*/
int IsPrime(int n) {
    int i, up;
    if (n <= 1) return 0;
    up = sqrt(n);
    for (i = 2; i <= up; ++i) {
        if (n % i == 0) return 0;
    }
    return 1;
}

/*
��ʮ���Ƶ�Nת��ΪD���Ƶ��봮����ת֮�������ʮ����ֵ��
*/
int Convert(int N, int D) {
    int ans = 0;
    while (N) {
        int d = N % D;
        ans = ans * D + d;
        N /= D;
    }
    return ans;
}

void TestConvert(void) {
    printf("%d %d\n", 23, Convert(23, 10));
}

int main(int argc, char* argv[]) {
    int N, D;

    //	TestConvert();
    //	return 0;
    freopen("./in.txt", "r", stdin);

    while (scanf("%d", &N), N >= 0) {
        int R;
        scanf("%d", &D);
        if (N == 1 || N == 0) {
            puts("No");
            continue;
        }

        R = Convert(N, D);
        if (IsPrime(N) && IsPrime(R)) {
            puts("Yes");
        } else {
            puts("No");
        }
    }

    return 0;
}
