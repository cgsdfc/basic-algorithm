#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
预计算 所有N^P 小于等于 N 的数，
因为在枚举因子时，其实枚举的是因子的幂，
并且因子的幂比因子大，所以枚举复杂度会下降。
*/

// 使用整数快速幂来计算所有的pow操作，比系统的pow要快。
static int Power(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) { ans *= a; }
        a *= a;
        b >>= 1;
    }
    return ans;
}

/*
n <= N^(1/P)，当N最大，P最小，即N=400，P=2时，n取得上界，
即20.
*/
#define MAXF 40
/*
fac[i]=i^P.
*/
struct {
    int data[MAXF];
    int len;
} fac;

/*
生成的因子序列最大长度？
就是K的最大值。
*/
#define MAXK (400 + 1)

typedef struct List {
    int data[MAXK];
    int len;
} List;

// 因子全局，局部最大值。
static List ans, temp;
static int MaxSum = -1;

static int N, K, P;

void Init(int N, int P) {
    int i = 0;
    int p = 0;
    while (p <= N) {
        p = Power(i, P);
        fac.data[fac.len++] = p;
        ++i;
    }
}

/*
得出fac数组后，问题就转化为在集合中查找元素可重复的子集，
使得子集满足条件并且某个特性最大的问题，
套用模板即可。
*/

static void DFS(int index, int nowK, int nowN, int nowSum) {
    if (nowK == K && nowN == N) {
        // 一个解。
        if (nowSum > MaxSum) {
            /*
            枚举的顺序，保证了temp数组是递减的，并且每次的temp是字典序递减的。
            */
            MaxSum = nowSum;
            ans = temp;
        }
        return;
    }
    /*
    解未出现，但是出现了必然没解的情况。
    1. nowK == K，但 nowN != N
    2. nowK < K，但 nowN >= N
    */
    if (nowK == K || nowN >= N) { return; }
    /*
    模板里关于元素可重复的两种情况：
    1. 选当前元素，然后继续考虑当前元素。解释一下为什么：
    因为对于每一个元素，都可以选 0-m 个，如果是0个，那就考虑下一个元素；
    如果不是0个，那就意味着可以一直选，直到到达边界条件，这样才能知道最多可以选多少。
    因为如果没有限制条件的话，是可以有无序多个的。
    2. 不选当前元素，然后继续考虑下一个元素。
    */

    if (index < 1) {
        // 因子不考虑 0.
        return;
    }

    // 选当前元素。
    temp.data[temp.len++] = index;
    DFS(index, nowK + 1, nowN + fac.data[index], nowSum + index);
    temp.len--;

    // 不选当前元素。
    DFS(index - 1, nowK, nowN, nowSum);
}

int Main2(void) {
#ifndef ONLINE_JUDGE
    freopen("./in.txt", "r", stdin);
#endif

    scanf("%d%d%d", &N, &K, &P);
    Init(N, P);
    DFS(fac.len - 1, 0, 0, 0);

    if (MaxSum == -1) {
        // 没有一个合法解。
        printf("Impossible\n");
    } else {
        int i;
        // 169 = 6^2 + 6^2 + 6^2 + 6^2 + 5^2
        printf("%d = ", N);
        for (i = 0; i < ans.len; ++i) {
            printf("%d^%d%s", ans.data[i], P, i == ans.len - 1 ? "\n" : " + ");
        }
    }
    return 0;
}

#ifdef ONLINE_JUDGE
int main(void) {
    return Main2();
}
#endif

/*
这个解法 257 ms，
比 Main1 的解法 659 ms 快。
*/
