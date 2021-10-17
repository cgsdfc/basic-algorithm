#include <algorithm>
#include <cassert>
#include <cstdio>
using namespace std;

#define MAXN 105

int N;
int G[MAXN][MAXN];
const int INF = 1e9;
bool vis[MAXN];
int d[MAXN];

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
要求保持图的连通性，且边权和最小的子图。
值得注意的是，在有负权的图，这不等于求最小生成树，因为正权是越少越好，但是负权是越多越好的，
这恰好违反了生成树是使得图保持联通的边最少的子图。
设想有一条负权边，删除或者保留，都不影响联通性，但是加入这条边会使边权和更小，所以要保留它，
即使违反树的性质。

由上述可知，最小生成树问题，实际上等价于求非负边权图的保留图的联通性的边权和最小的子图。
但是不等价于求一般图的保留联通性的边权和最小的子图，因为后者的结构不是树。
*/

/*
本题的图是完全图，即稠密图，适合Prim。点数较少，适合邻接矩阵。
保证为联通图，不需要检测。
*/

int Prim(int s) {
    fill(vis, vis + MAXN, false);
    fill(d, d + MAXN, INF);
    d[s] = 0;
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int u = -1;
        int MIN = INF;
        for (int j = 1; j <= N; ++j) {
            if (!vis[j] && d[j] < MIN) {
                MIN = d[j];
                u = j;
            }
        }
        assert(u != -1);
        vis[u] = true;
        ans += d[u];
        for (int j = 1; j <= N; ++j) {
            if (!vis[j] && G[u][j] != INF && G[u][j] < d[j]) { d[j] = G[u][j]; }
        }
    }
    return ans;
}

int main(int argc, char** argv) {
    while (scanf("%d", &N), N) {
        int M = N * (N - 1) / 2;
        fill(G[0], G[0] + MAXN * MAXN, INF);
        while (M--) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            G[u][v] = G[v][u] = d;
        }
        int ans = Prim(1);
        printf("%d\n", ans);
    }

    return 0;
}
