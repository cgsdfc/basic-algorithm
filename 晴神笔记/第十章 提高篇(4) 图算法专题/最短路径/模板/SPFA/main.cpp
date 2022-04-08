/*
SPFA是Bellman的优化版本，具有相同功能，但是复杂度为O(kE)，Bellman的复杂度为O(VE)。
Shortest Path Fast Algorithm，国人提出的最短路优化算法。
*/

/*
关于inq的作用。
1. 节点出队后，inq设为false。
2. 只有inq为false的节点，才能入队。

所以，一个节点u，如果当前在队列内，则inq为true，否则为false。
作用：
1. 队列里的节点是无重复的！因为一个节点在队列里，那么就不会再次入队了。
2. 队列里的元素可以看作集合！因为无重复。
3.
假设某轮循环结束后，队列集合为S，一轮操作中，既有出队，又有入队，当S集合完全出队时（
强调队列的前段部分的S的元素），队列同时有一个新的集合（可能空集），即N。显然N是由S扩展而来的。
并且N和S可能有交集。N如果为空，说明算法收敛了；否则就是未收敛，就可以继续扩展。

如果不维护inq数组，则队列里面就可能有重复元素，那么就不是集合了，算法最终也能收敛（在存在最短路的前提下），
这部分暂时不明白。

另外，SPFA有多种优化，这里不涉及。
SPFA可能退化为Bellman的复杂度，即O(VE)，对于稠密图，即为O(V^3)。
故非负边权的图，用Dijkstra好，复杂度永远是 O(VlogV+E)，对于稠密图，即为O(V^2)。
为什么Dijk比SPFA快？因为它假设了非负边权，导致贪心策略是正确的，自然比DP要低一个数量级。

Dijk 是 PQ 优化，SPFA 是 Q 优化。

为什么SPFA优化了Bellman？因为：
1. Bellman每一轮都是无脑地遍历所有边，但其实只有那些在上一轮中某个结点距离发生了变化
的边才有处理的价值，所以不需要每轮处理所有的边；
2. Bellman总是要进行V-1轮循环，
而当所有结点的距离都不变了，再怎么迭代也不会变。所以V-1轮只是理论上的轮数，实际上可能不需要这么多轮。
对于这种某轮的变化触发下一轮的新变化的逻辑，用队列来跟踪每轮的变化是合适的。
*/

#include <queue>  // SPFA必备。
#include <vector>
using namespace std;

#define MAXN 505  // 节点数上界。

struct Node {
    int v, dis;
    Node(int _v, int _dis): v(_v), dis(_dis) {}
};

vector<Node> Adj[MAXN];

bool inq[MAXN];  // 保证队列内元素唯一性。
int num[MAXN];   // 计数某节点入队次数，判负环。
int d[MAXN];     // 最短距离。

int N;  // 节点数。
const int INF = 1e9;

bool SPFA(int s) {
    fill(d, d + N, INF);
    fill(inq, inq + N, false);
    fill(num, num + N, 0);

    queue<int> Q;
    // 队列Q跟踪那些节点被松弛了，那么这些节点就可能触发新的松弛。
    Q.push(s);
    inq[s] = true;
    d[s] = 0;
    num[s]++;
    while (!Q.empty()) {
        // 取队首元素。
        int u = Q.front();
        Q.pop();
        // 既然出队了，inq设为false。
        inq[u] = false;
        // 遍历u的邻居进行松弛。
        for (int j = 0; j < Adj[u].size(); j++) {
            int v = Adj[u][j].v;
            int dis = Adj[u][j].dis;
            if (d[u] + dis < d[v]) {
                d[v] = d[u] + dis;
                // 注意，更新d数组不受inq的约束。
                if (!inq[v]) {
                    Q.push(v);
                    // 一个结点可以重复入队多次。
                    inq[v] = true;
                    num[v]++;
                    // 注意，先增加num，然后再检测。
                    if (num[v] >= N) {
                        // 有负环的条件是某节点入队次数超过N-1.
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main(int argc, char** argv) {
    return 0;
}
