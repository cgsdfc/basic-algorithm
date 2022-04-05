#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
分解质因子的模板。
首先打素数表，如果被分解的数是int范围的，用10e5的表即可。
因为：
1. 接近int上限的大素数，自己是自己的因子，这种因子是不会存在素数表里的。
由后面的算法可知，这种大于sqrtN的因子不是从素数表里查的。
2.
其他因子，即小于等于sqrtN的因子，因为N是int范围的，所以sqrtN的上界为2^15左右，
并且是这个附近的一个素数，2^15大约65536/2，因此10e5绝对足够了。

估计long long的N所需的素数表大小：
只需要针对第一种因子，即小于等于sqrtN的因子即可。long long是2^63，sqrtN是2^31，
约等于10e9，因此需要10e10的素数表。这个恐怕是爆内存的。
*/

#define MAXN 100000
int p[MAXN];
int prime[MAXN];  // 从小到大枚举素数，需要素数的确定数值。
int pNum;

/*
第一步，打素数表。
10e5的线性操作是完全可以接受的，所以就直接打到MAXN即可。
一般由N（待分解的数）的上限确定素数表的上限的方法：

        比sqrtN大一个数量级。

因为小于等于sqrtN的素数P是除了N本身外，N最大的可能的素因子，
考虑到素数表的上限要包含这个P，所以MAXN比P大一个数量级，就肯定包含了。
比如P是23时，MAXN取1000.
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
记录一个素因子及其重数的结构体。
当分解素因子时，一个素因子可以有多重。
N的全部素因子构成了一个素数的多重集合。
*/
typedef struct Factor {
    int x;
    int cnt;
} Factor;

/*
对于int范围的数，前十个素数的乘积就超过了int的最大值，
因此只需要以前十个素数为元素，就可以表示int的所有数字。
对于long long，可以设为20.
*/
#define MAXF 10

/*
分解素因子。
返回factors数组大小。
一个正整数的素因子有两种情况：
1. 全部小于等于sqrtN。
2. 有且仅有一个大于sqrtN的，其余全部小于等于sqrtN。

因此算法先枚举小于等于sqrtN的所有素数，用这些素数去除N（如果整除），
使N不断缩小。最后再检查第二种情况，也就是此时N还不等于1（还有因此存在，并且
大于sqrt），那么再增加一个因子。
*/
int DoFactor(int N, Factor factors[]) {
    int i;
    // 决定算法复杂度关键的sqrt，千万不是N。
    int sqr = sqrt(N);
    int num = 0;

    assert(pNum);

    // 枚举小于sqrt的所有素数。
    for (i = 0; i < pNum && prime[i] <= sqr; ++i) {
        int p = prime[i];
        if (N % p == 0) {
            // 找到一个新的因子。
            factors[num].x = p;
            factors[num].cnt = 0;
            // 把该因子的全部重复找出来。
            // 不需要循环的，x=p; cnt=N/p; N%=p;
            while (N % p == 0) {
                factors[num].cnt++;
                N /= p;
            }
            ++num;  // 记得增加num。
        }
    }
    // 如果第二种因子存在。
    if (N != 1) {
        factors[num].x = N;
        factors[num].cnt = 1;
        ++num;
    }
    return num;
}

/*
计算正整数N的所有因子个数。
先计算出素因子集合，然后计算子集数，
与计算所有因子不同，所有因子个数不需要递归。
只要乘法原理即可。
*/
int TotalFactors(int N) {
    int ans = 1;
    int num;
    int i;
    Factor fac[MAXF];

    num = DoFactor(N, fac);
    for (i = 0; i < num; ++i) {
        /*
        对于每一个因子，有cnt+1种选择，即选取0--cnt个。
        */
        ans *= fac[i].cnt + 1;
    }
    return ans;
}

/*
N的所有因子之和。
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
        // 计算 1+p+p**2+p**3+...+p**e
        for (j = 0; j <= fac[i].cnt; ++j) {
            sum = sum * fac[i].x + 1;
        }
        ans *= sum;
    }
    return ans;
}

/*
计算N的所有因子，注意不是素因子，而是整除N的数。
并且要求不重复。
1是任何正整数的因子，N本身是任何正整数的因子，但有些题目要排除N本身。
这是不需要用到素数的，并且复杂度和分解素因子一样都是sqrtN。
注意：
1. 此算法输出的因子是无序的，因为复杂度是sqrtN的缘故，总是一小一大的输出因子。
若想有序则保存到数组里排序。数组开多大？
2. 此算法可以计算因子个数和因子和。
*/
void AllFactor(int N) {
    int sqr;
    int i;
    int cnt = 0;
    int sum = 0;

    sqr = sqrt(N);
    for (i = 1; i <= sqr; ++i) {
        if (N % i == 0) {
            // i是一个因子。
            int p = N / i;  // p是和i对应的另一个因子。
            ++cnt;
            sum += i;
            printf("%d ", i);
            if (p != i) {
                // 这里可以判定p!=N才进入，这样就把N排除了。
                // 当i=1时，P=N。
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
