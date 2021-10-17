#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
背包问题：
有N个物品，每个物品有体积和价值两个属性，并以数组的形式给出，
现在需要从中选出若干物品放入容量为V的背包中，在总体积不超过V的条件下，
使得总价值最大，求最大的总价值。

问题的本质是枚举具有N个元素的全集的所有子集，包括不同元素数量的子集，也包括空集。
下面这种枚举方法会无重复的枚举所有子集，因此复杂度是 2^N 。
*/

/*
保存物品选择方案。
*/
#define MAXN 100
struct {
    int data[MAXN];
    int len;
} ans, temp;

int N;                 // 物品总数。
int V;                 // 最大体积。
int MaxValue = 0;      // 全局最大价值。
int W[MAXN], C[MAXN];  // 物品的体积 ，价值。

/*
按照物品的下标，从大到小考虑每一件物品，对于每一件物品index有两种选择：
1. 选该物品。
2. 不选该物品。
两种情况的后续都是继续考虑下一件物品，即index+1 。
边界：
当N件物品都考虑过则得出了一个无重复的，完整的方案，即物品的一个子集。
此时应该检验方案是否合法（总体积小于V），并且更新总价值的最大值。

index：当前要考虑的物品。
nowW：当前已选物品的总体积。
nowC：当前已选物品的总价值。
*/

void DFS(int index, int nowW, int nowC) {
    if (index == N) {
        if (nowW <= V && nowC > MaxValue) {
            MaxValue = nowC;
            ans = temp;
        }
        return;
    }
    DFS(index + 1, nowW, nowC);  // 不选 index 物品。

    temp.data[temp.len++] = index;
    DFS(index + 1, nowW + W[index], nowC + C[index]);  // 选 index 物品。
    --temp.len;
}

/*
剪枝版本。
*/

void DFS2(int index, int nowW, int nowC) {
    if (index == N) {
        return;  // 注意：每选一件物品就会更新最大价值，而不是等一个完整方案出来再更新。
                 // 故此处不必更新。
    }
    DFS2(index + 1, nowW, nowC);  // 不选，则两个参数都不用更新，但是index要更新。
    /*
    剪枝逻辑：
    在走岔道之前，先判定一下这条岔道是否是没有结果的，
    即先预判，如果现在做这个选择，则会不会违反限制条件。
    */
    if (nowW + W[index] <= V) {
        if (nowC + C[index] > MaxValue) { MaxValue = nowC + C[index]; }
        DFS2(index + 1, nowW + W[index], nowC + C[index]);
    }
}

void Solve1(void) {
    int i;
    scanf("%d%d", &N, &V);
    for (i = 0; i < N; ++i) {
        scanf("%d", &W[i]);
    }
    for (i = 0; i < N; ++i) {
        scanf("%d", &C[i]);
    }
    DFS(0, 0, 0);
    printf("%d\n", MaxValue);
    for (i = 0; i < ans.len; ++i) {
        printf("%d%s", ans.data[i], i == ans.len - 1 ? "\n" : " ");
    }
}
