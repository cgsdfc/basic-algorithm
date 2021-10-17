#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
给定N个整数，从中选择K个数，使得这K个数之和恰好等于一个给定的整数 X；
如果有多种方案，选择它们中元素平方和最大的一个。

问题的本质是枚举一个有N个元素的全集的K元子集。
由于限制了子集的大小，所以不再是枚举所有子集，复杂度是C(N,K)，
即从N个元素选出K个来的方法数（组合数）。

DFS的方法是在枚举子集的基础上增加对已枚举元素个数的限制。
*/

int N;            // 全集的大小。
int K;            // 待枚举的子集的大小。K<=N
int X;            // 限制，子集元素的和等于X。
int MaxSum = -1;  // 最大平方和。

#define MAXN 100
// 全集的元素。
int A[MAXN];

// 保存最优方案（子集）
struct {
    int data[MAXN];
    int len;
} ans, temp;

/*
和子集枚举有相同的框架，但是把枚举的子集大小限制在K，
即，只考虑K阶子集。

index：当前要考虑的元素下标。
nowK：当前产生的子集大小（对应 temp.len）。
nowX：当前子集的元素和。
nowS：当前子集元素的平方和。
*/
static void DFS(int index, int nowK, int nowX, int nowS) {
    int x;
    /*
    特判：当前状态有解，应该更新最大值。
    */
    if (nowK == K && nowX == X) {
        if (nowS > MaxSum) {
            MaxSum = nowS;
            ans = temp;
        }
        return;
    }
    /*
    特判：当前状态无解。
    */
    if (index == N || nowK > K || nowX > X) { return; }
    /*
    考虑当前的数，然后继续。
    */
    x = A[index];
    temp.data[temp.len++] = x;
    DFS(index + 1, nowK + 1, nowX + x, nowS + x * x);
    --temp.len;

    // 不选当前数。
    DFS(index + 1, nowK, nowX, nowS);
}

/*
问题的变式

元素可重复的K阶子集。
对于每个全集的元素X，它可以在子集中出现0到多次。
注意这样的子集的数量仍是有限的，因为限制了子集的大小为K，
如果不加限制，则这样的子集数量是无限的。

问题就变成了枚举元素可重复的K阶子集。
岔道口变成：
1. 不选当前元素，考虑下一个元素。
2. 选当前元素，并且继续考虑当前元素。

死胡同仍然是：
1. 满K个元素。
2. N个元素考虑完。
*/
static void DFS2(int index, int nowK, int nowX, int nowS) {
    int x;
    /*
    特判：当前状态有解，应该更新最大值。
    */
    if (nowK == K && nowX == X) {
        if (nowS > MaxSum) {
            MaxSum = nowS;
            ans = temp;
        }
        return;
    }
    /*
    特判：当前状态无解。
    */
    if (index == N || nowK > K || nowX > X) { return; }
    /*
    考虑当前的数，然后继续。
    */
    x = A[index];
    temp.data[temp.len++] = x;
    /*
    元素可重复的修改：
    取index后，继续考虑index，直到到达边界，就会通过下面的代码
    考虑其他元素。即 index 参数这里，index+1 改为 index。
    */
    DFS2(index, nowK + 1, nowX + x, nowS + x * x);
    --temp.len;

    // 不选当前数。
    DFS2(index + 1, nowK, nowX, nowS);
}
