#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
�ֽ������ӵ�ģ�塣
���ȴ�������������ֽ������int��Χ�ģ���10e5�ı��ɡ�
��Ϊ��
1. �ӽ�int���޵Ĵ��������Լ����Լ������ӣ����������ǲ��������������ġ�
�ɺ�����㷨��֪�����ִ���sqrtN�����Ӳ��Ǵ����������ġ�
2.
�������ӣ���С�ڵ���sqrtN�����ӣ���ΪN��int��Χ�ģ�����sqrtN���Ͻ�Ϊ2^15���ң�
���������������һ��������2^15��Լ65536/2�����10e5�����㹻�ˡ�

����long long��N������������С��
ֻ��Ҫ��Ե�һ�����ӣ���С�ڵ���sqrtN�����Ӽ��ɡ�long long��2^63��sqrtN��2^31��
Լ����10e9�������Ҫ10e10����������������Ǳ��ڴ�ġ�
*/

#define MAXN 100000
int p[MAXN];
int prime[MAXN];  // ��С����ö����������Ҫ������ȷ����ֵ��
int pNum;

/*
��һ������������
10e5�����Բ�������ȫ���Խ��ܵģ����Ծ�ֱ�Ӵ�MAXN���ɡ�
һ����N�����ֽ������������ȷ������������޵ķ�����

        ��sqrtN��һ����������

��ΪС�ڵ���sqrtN������P�ǳ���N�����⣬N���Ŀ��ܵ������ӣ�
���ǵ������������Ҫ�������P������MAXN��P��һ�����������Ϳ϶������ˡ�
����P��23ʱ��MAXNȡ1000.
*/

void FindPrime(void) {
    int i, j;
    for (i = 2; i < MAXN; ++i) {
        if (!p[i]) {
            prime[pNum++] = i;
            for (j = 2 * i; j < MAXN; j += i) {
                p[j] = 1;
            }
        }
    }
}

/*
��¼һ�������Ӽ��������Ľṹ�塣
���ֽ�������ʱ��һ�������ӿ����ж��ء�
N��ȫ�������ӹ�����һ�������Ķ��ؼ��ϡ�
*/
typedef struct Factor {
    int x;
    int cnt;
} Factor;

/*
����int��Χ������ǰʮ�������ĳ˻��ͳ�����int�����ֵ��
���ֻ��Ҫ��ǰʮ������ΪԪ�أ��Ϳ��Ա�ʾint���������֡�
����long long��������Ϊ20.
*/
#define MAXF 10

/*
�ֽ������ӡ�
����factors�����С��
һ���������������������������
1. ȫ��С�ڵ���sqrtN��
2. ���ҽ���һ������sqrtN�ģ�����ȫ��С�ڵ���sqrtN��

����㷨��ö��С�ڵ���sqrtN����������������Щ����ȥ��N�������������
ʹN������С������ټ��ڶ��������Ҳ���Ǵ�ʱN��������1��������˴��ڣ�����
����sqrt������ô������һ�����ӡ�
*/
int DoFactor(int N, Factor factors[]) {
    int i;
    // �����㷨���Ӷȹؼ���sqrt��ǧ����N��
    int sqr = sqrt(N);
    int num = 0;

    assert(pNum);

    // ö��С��sqrt������������
    for (i = 0; i < pNum && prime[i] <= sqr; ++i) {
        int p = prime[i];
        if (N % p == 0) {
            // �ҵ�һ���µ����ӡ�
            factors[num].x = p;
            factors[num].cnt = 0;
            // �Ѹ����ӵ�ȫ���ظ��ҳ�����
            // ����Ҫѭ���ģ�x=p; cnt=N/p; N%=p;
            while (N % p == 0) {
                factors[num].cnt++;
                N /= p;
            }
            ++num;  // �ǵ�����num��
        }
    }
    // ����ڶ������Ӵ��ڡ�
    if (N != 1) {
        factors[num].x = N;
        factors[num].cnt = 1;
        ++num;
    }
    return num;
}

/*
����������N���������Ӹ�����
�ȼ���������Ӽ��ϣ�Ȼ������Ӽ�����
������������Ӳ�ͬ���������Ӹ�������Ҫ�ݹ顣
ֻҪ�˷�ԭ���ɡ�
*/
int TotalFactors(int N) {
    int ans = 1;
    int num;
    int i;
    Factor fac[MAXF];

    num = DoFactor(N, fac);
    for (i = 0; i < num; ++i) {
        /*
        ����ÿһ�����ӣ���cnt+1��ѡ�񣬼�ѡȡ0--cnt����
        */
        ans *= fac[i].cnt + 1;
    }
    return ans;
}

/*
N����������֮�͡�
*/
int TotalFactorSum(int N) {
    int ans = 1;
    int i;
    int num;
    Factor fac[MAXF];

    num = DoFactor(N, fac);
    for (i = 0; i < num; ++i) {
        int sum = 0;
        int j;
        // ���� 1+p+p**2+p**3+...+p**e
        for (j = 0; j <= fac[i].cnt; ++j) {
            sum = sum * fac[i].x + 1;
        }
        ans *= sum;
    }
    return ans;
}

/*
����N���������ӣ�ע�ⲻ�������ӣ���������N������
����Ҫ���ظ���
1���κ������������ӣ�N�������κ������������ӣ�����Щ��ĿҪ�ų�N����
���ǲ���Ҫ�õ������ģ����Ҹ��ӶȺͷֽ�������һ������sqrtN��
ע�⣺
1. ���㷨���������������ģ���Ϊ���Ӷ���sqrtN��Ե�ʣ�����һСһ���������ӡ�
���������򱣴浽�������������鿪���
2. ���㷨���Լ������Ӹ��������Ӻ͡�
*/
void AllFactor(int N) {
    int sqr;
    int i;
    int cnt = 0;
    int sum = 0;

    sqr = sqrt(N);
    for (i = 1; i <= sqr; ++i) {
        if (N % i == 0) {
            // i��һ�����ӡ�
            int p = N / i;  // p�Ǻ�i��Ӧ����һ�����ӡ�
            ++cnt;
            sum += i;
            printf("%d ", i);
            if (p != i) {
                // ��������ж�p!=N�Ž��룬�����Ͱ�N�ų��ˡ�
                // ��i=1ʱ��P=N��
                ++cnt;
                sum += p;
                printf("%d ", p);
            }
        }
    }
    putchar('\n');
    printf("cnt %d sum %d\n", cnt, sum);
}

void TestDoFactor(void) {
    int N;

    FindPrime();
    while (scanf("%d", &N) != EOF) {
        Factor factors[MAXF];
        int num;
        int i;

        num = DoFactor(N, factors);
        for (i = 0; i < num; ++i) {
            printf("%d^%d ", factors[i].x, factors[i].cnt);
        }
        putchar('\n');
    }
}

void TestAllFactor(void) {
    int N;
    while (scanf("%d", &N) != EOF) {
        AllFactor(N);
    }
}

int main(int argc, char* argv[]) {
    TestAllFactor();
    return 0;
}
