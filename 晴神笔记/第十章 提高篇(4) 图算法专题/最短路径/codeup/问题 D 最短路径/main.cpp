#include <algorithm>
#include <cstdio>
#include <queue>
//#include <map> // 节点的编号
using namespace std;

#define MAXN 1005
const int INF = 1e9;

struct Node {
  int v, dis;
  Node(int _v, int _d) : v(_v), dis(_d) {}
  friend bool operator<(const Node &a, const Node &b) { return a.dis > b.dis; }
};

int N, M, S, T; // 点数，边数，起点，终点。
// vector<Node> Adj[MAXN];
int G[MAXN][MAXN];
int d[MAXN];
bool vis[MAXN];
// DFS求字典序最小的路径。
// vector<int> pre[MAXN], tempPath, path;
int pre[MAXN];

/*
点是1000，边是10000，边比点多，而且边权非负，用Dijkstra比较靠谱。
*/
void Dijkstra(int s) {
  fill(vis, vis + MAXN, false);
  fill(d, d + MAXN, INF);
  priority_queue<Node> Q;
  Q.push(Node(s, 0));
  d[s] = 0;
  for (int i = 0; i < MAXN; ++i) {
    pre[i] = i;
  }
  while (!Q.empty()) {
    int u = Q.top().v;
    Q.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    for (int v = 1; v <= N; ++v) {
      if (!vis[v] && G[u][v] != INF) {
        int dis = G[u][v];
        if (d[u] + dis < d[v]) {
          d[v] = d[u] + dis;
          pre[v] = u;
          Q.push(Node(v, d[v]));
        } else if (d[u] + dis == d[v] && u < pre[v]) {
          pre[v] = u;
        }
      }
    }
  }
}

void DFS(int s, int v) {
  if (s == v) {
    printf("%d ", s);
    return;
  }
  DFS(s, pre[v]);
  printf("%d ", v);
}

int main(int argc, char **argv) {
  while (scanf("%d%d%d%d", &N, &M, &S, &T) != EOF) {
    fill(G[0], G[0] + MAXN * MAXN, INF);
    while (M--) {
      int a, b, d;
      scanf("%d%d%d", &a, &b, &d);
      // 无向图，并且假设节点是1--N。
      /*
      注意有重边。
      */
      d = min(d, G[a][b]);
      G[a][b] = G[b][a] = d;
    }
    Dijkstra(S);
    if (d[T] == INF) {
      puts("can't arrive");
    } else {
      printf("%d\n", d[T]);
      DFS(S, T);
      printf("\n");
    }
  }
  return 0;
}
