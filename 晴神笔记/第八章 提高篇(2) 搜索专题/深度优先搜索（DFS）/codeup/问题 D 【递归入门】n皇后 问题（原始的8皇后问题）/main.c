#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
N皇后问题
每一个皇后放在不同行，不同列，如此放完N个后，检查每个皇后
是否两两不在一条对角线。
采用枚举全排列的方法，已经满足了不在同一行、同一列的要求，剩下的
第一种放法，按照字典序递增枚举，就是枚举1--N的全排列。
在全排列的基础上判定解是否满足对角线原则。
*/

#define MAXN 15
int N;
int ans[MAXN];
int hashtable[MAXN];
int has;  // 是否有解。

/*
检查当前排列是否满足对角线原则。
*/
int OK(void) {
    int i;
    for (i = 0; i < N - 1; ++i) {
        int j;
        for (j = i + 1; j < N; ++j) {
            /*
            条件：行号之差的绝对值等于列号之差的绝对值，
            则两个皇后在一条对角线。
            */
            if (abs(i - j) == abs(ans[i] - ans[j])) return 0;
        }
    }
    return 1;
}

// 打印规模为N的N皇后方案，以及是否存在一个方案。
void DFS(int index) {
    int i;
    if (index == N && OK()) {
        for (i = 0; i < N; ++i) {
            printf("%d%s", ans[i], i == N - 1 ? "\n" : " ");
        }
        has = 1;
        return;
    }
    if (index == N) { return; }
    // 剩下就是全排列的逻辑了。
    for (i = 1; i <= N; ++i) {
        /*
        找到当前没用过的最小数。
        */
        if (!hashtable[i]) {
            /*
            检查一下放i是否会和之前的皇后存在对角线的冲突。（剪枝）
            */
            int ok = 1;
            int j;
            for (j = 0; j < index; ++j) {
                // index是当前的行，i是当前的列，j是之前的行，ans[j]是之前的列。
                if (abs(index - j) == abs(i - ans[j])) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                hashtable[i] = 1;
                ans[index] = i;
                DFS(index + 1);
                hashtable[i] = 0;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    while (scanf("%d", &N) != EOF) {
        has = 0;
        DFS(0);
        if (!has) { puts("no solute!"); }
    }
    return 0;
}
