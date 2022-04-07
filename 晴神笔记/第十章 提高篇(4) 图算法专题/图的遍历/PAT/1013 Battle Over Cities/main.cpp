#include <algorithm>
#include <cassert>
#include <cstdio>

using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
给定一个联通无向图，删去其中一个点，问需要加多少边才能使得剩下的点仍是联通图。
只有计算删点后的图有多少联通分量即可（记为C个），加边数E=C-1.
（使C个节点联通的最小边数为C-1）
*/

/*
因为要支持快速删边和加边，并且N不大，用邻接矩阵即可。
删点用一个hash数组表示某点被删了。
*/

int N, M, K;  // 节点数，边数，删点数。

#define MAXN 1005  // 节点下标1--N。

bool G[MAXN][MAXN];
bool vis[MAXN];  // DFS必备。
// bool Del[MAXN];
int Del;

// 求联通分量用DFS即可。

void DFS(int u) {
    vis[u] = true;
    for (int v = 1; v <= N; ++v) {
        if (!vis[v] && G[u][v] && v != Del) { DFS(v); }
    }
}

// 删掉Q点，返回需要添加的边数。
int DFSTrave() {
    int ans = 0;  // 联通分量数。
    // BUG点：
    // 注意下标1-N对fill的影响！
    // 实际上要把[1--N]都设为false.
    fill(vis + 1, vis + N + 1, false);

    for (int v = 1; v <= N; ++v) {
        if (!vis[v] && v != Del) {
            // 既不访问死点，也不重复访问。
            ++ans; // 统计联通分量数量。
            DFS(v);
        }
    }
    assert(ans >= 0);
    return ans - 1;
}

/*
时间复杂度，删点K次，每次遍历全图，则：
O(KV)
*/

int main(int argc, char** argv) {
    scanf("%d%d%d", &N, &M, &K);
    while (M--) {
        int i, j;
        scanf("%d%d", &i, &j);
        G[i][j] = G[j][i] = true;
    }
    while (K--) {
        // 查询。每次只删除一个点。
        scanf("%d", &Del);
        int ans = DFSTrave();
        printf("%d\n", ans);
    }
    return 0;
}
