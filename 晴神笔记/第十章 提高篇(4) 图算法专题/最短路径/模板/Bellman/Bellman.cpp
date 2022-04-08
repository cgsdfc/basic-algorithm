/*
Bellman-Ford 算法（BF算法）。

计算单源最短路，可以处理负边权，并且检测负环。

引入负边权后出现的问题：如果存在从源点可达的负环，则从该源点出发的单源最短路不存在，
否则最短路一定存在。
正环，零环，负环，是根据环的边权和为正数，零和负数分别区分的。其中正环和零环不影响
最短路的求解，而负环的存在可能使得最短路不存在。

为什么源点可达负环使得最短路不存在。

假设S为源点，V为任意从S可达的点，因为负环是可达的，V也是可达的，所以存在路径：
先从S到达负环，再从负环到达V，这是一条从S到V的路径，记为P。现在在P的基础上，
在经过负环时，多绕负环一圈，则得出P2的边权比P1更小。以此类推，可以通过不断的绕负环一周，
使得边权和不断减小，并且没有下界，所以最短路不存在（因为总能够找到比当前的路更短的路，
没有最短，只有更短）。存在可达负环是最短路不存在的充要条件。
注意，只要存在S可达的负环， 则对任意节点V来说，S到V的最短路都不存在。

Bellman算法在最短路不存在时，返回false，否则返回true，并求出最短路。

实现注意：
1. 算法要遍历全部边，所以使用邻接表。
2. 遍历所有边的做法是，对每一个节点，遍历它的所有出边，即用两重循环遍历邻接表。
3.
算法主体有V-1轮，每轮计算出最短路树的一层的全部节点的距离，因为最短路树最多V层，
而第一层是根，即源点S，在初始化确定，故算法最多需要V-1次循环。实际上不一定需要V-1次。
4.
在主体循环后面，有一段检测负环的逻辑，决定了算法的返回值。为什么这样呢？因为如果最短路存在，
则经过V-1轮的计算，必定能确定全部节点的距离，并且不能再松弛。如果最短路不存在，则可以无限松弛下去。
换句话说，如果存在最短路，则算法迭代到数组d不再变化，如果最短路不存在，则算法将无限迭代下去。
现在知道了在存在最短路的前提下，算法最多迭代V-1轮，所以先假设最短路存在，迭代V-1轮，然后检测是否
能够继续迭代，如果可以，则最短路不存在。

当题目保证不存在负环时，可以不写检测逻辑，并且返回void。

Bellman算法的复杂度为 O(VE)。
*/

#include <set>  // 求全部最短路必备。
#include <vector>
using namespace std;

#define MAXN 505  // 节点上界。

// 边。
struct Node {
    int v;
    int dis;
};

// 也可以保存为edge list结构？
vector<Node> Adj[MAXN];  // 邻接表。

int d[MAXN];  // 距离数组。

int N;  // 节点数。
// 算法不需要vis数组。
const int INF = 1e9;

/*
能处理负边权的单源最短路算法Bellman。
s：源点。
如果最短路存在（不存在s可达的负环），返回true，否则返回false。
*/
bool Bellman(int s) {
    fill(d, d + N, INF);
    d[s] = 0;
    // N-1轮松弛。
    int T = N - 1;
    while (T--) {
        // 每轮松弛，访问所有边。
        for (int u = 0; u < N; ++u) {
            for (int i = 0; i < Adj[u].size(); ++i) {
                int v = Adj[u][i].v;
                int dis = Adj[u][i].dis;
                // u->v dis
                if (d[u] + dis < d[v]) {
                    // len(s-->u->v) < len(s-->v)
                    // 对于s到v的路径来说，经过u的路径更短。
                    d[v] = d[u] + dis;
                }
            }
        }
    }
    // 检测负环，实际上就是再次松弛操作，检测是否能松弛。
    for (int u = 0; u < N; ++u) {
        for (int i = 0; i < Adj[u].size(); ++i) {
            int v = Adj[u][i].v;
            int dis = Adj[u][i].dis;
            if (d[u] + dis < d[v]) {
                // 还能够松弛，则有负环。
                return false;
            }
        }
    }
    // 无法松弛，则无负环。
    return true;
}

/*
提前退出优化。在V轮松弛中，如果某轮检测到无法再松弛，则返回true，
否则V轮结束后，返回false。这是一个逻辑等价的算法，但是可以减少迭代轮数。
*/
bool Bellman2(int s) {
    fill(d, d + N, INF);
    d[s] = 0;
    // N轮操作，边松弛，边检测是否能够松弛。
    int T = N;
    while (T--) {  // 最多进行V次就能判断是否存在负环。
        // 检测本轮结束后，是否改变了d数组。
        bool changed = false;
        // 每轮松弛，访问所有边。
        for (int u = 0; u < N; ++u) {
            for (int i = 0; i < Adj[u].size(); ++i) {
                int v = Adj[u][i].v;
                int dis = Adj[u][i].dis;
                // u->v dis
                if (d[u] + dis < d[v]) {
                    // len(s-->u->v) < len(s-->v)
                    // 对于s到v的路径来说，经过u的路径更短。
                    d[v] = d[u] + dis;
                    changed = true;
                }
            }
        }
        if (!changed) { return true; }
    }
    // 相当于把Bellman的V-1轮松弛和最后一轮的检测逻辑合并为V轮。
    return false;
}

/*
Bellman计算最短路数量和统计全部最短路。

在负环不存在的前提下（即保证最短路存在），算法只需要迭代V-1轮，不需要检测负环，
当然可以提前退出，但是优化并不明显。
*/
int num[MAXN];       // 记录s到u的路径数量。
set<int> pre[MAXN];  // 记录u的前驱。

void Bellman3(int s) {
    fill(d, d + N, INF);
    d[s] = 0;
    // N-1轮松弛。
    int T = N - 1;
    while (T--) {
        // 每轮松弛，访问所有边。
        for (int u = 0; u < N; ++u) {
            for (int i = 0; i < Adj[u].size(); ++i) {
                int v = Adj[u][i].v;
                int dis = Adj[u][i].dis;
                // u->v dis
                if (d[u] + dis < d[v]) {
                    // 对于s到v的路径来说，经过u的路径更短。
                    d[v] = d[u] + dis;
                    num[v] = num[u];
                    pre[v].clear();
                    pre[v].insert(u);
                } else if (d[u] + dis == d[v]) {
                    // 注意！
                    /*
                    这里，可能是一条相同长度的新路径，也可能是一条已经访问过的路径，
                    在Bellman的框架下，二者很难区分（是可以区分的）。如果u是新增的前驱，
                    即 pre[v]
                    没有u，那么就是新路径。如果u已经存在于v的前驱中，那么看num[v]
                    是否变化，但是现有框架无法得知这一点，所以为了简便起见，就重新计算num[v]，
                    而不是计算增量。具体方法是，先更新pre[v]，然后根据v的num等于v的前驱的num之和来计算。
                    显然，如果Pi是前驱i的一条路径，Pj是前驱j的一条路径，且i不等于j，则Pi和Pj是不同的路径，
                    所以上述计算是正确的。
                    */
                    // 因为存在重复访问的问题，所以重新计算num。
                    num[v] = 0;
                    pre[v].insert(u);
                    for (set<int>::iterator it = pre[v].begin(); it != pre[v].end(); ++it) {
                        num[v] += num[*it];  // 累计前驱的num之和。
                    }
                }
            }
        }
    }
}
