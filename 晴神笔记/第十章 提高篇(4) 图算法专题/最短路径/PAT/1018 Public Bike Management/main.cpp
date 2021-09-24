#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 505

int G[MAXN][MAXN];
int weight[MAXN]; // 点权，某车站有多少车。
int d[MAXN];
bool vis[MAXN];
int C, N, Sp, M;

const int INF = 1e9;

struct State {
  int send; // 如果当前收集的车不够分配，就要从总站发车。
  int coll; // 当前收集的车辆数。

  State(int s, int c) : send(s), coll(c) {}

  friend bool operator<(State a, State b) {
    if (a.send != b.send) {
      return a.send < b.send;
    }
    return a.coll < b.coll;
  }
};

// 全部路径，最优路径，临时路径。
vector<int> pre[MAXN], Path, tempPath;

struct Node {
  int v;
  int dis;
  Node(int _v, int _dis) : v(_v), dis(_dis) {}
  friend bool operator<(Node a, Node b) { return a.dis > b.dis; }
};

// 以距离为标尺求全部最短路径。
void Dijkstra(int s) {
  fill(d, d + MAXN, INF);
  fill(vis, vis + MAXN, false);
  d[s] = 0;
  priority_queue<Node> Q;
  Q.push(Node(s, 0));
  while (!Q.empty()) {
    int u = Q.top().v;
    Q.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = true;
    for (int v = 0; v <= N; ++v) {
      // 注意，全体节点是0--N。
      if (!vis[v] && G[u][v] != INF) {
        if (d[u] + G[u][v] < d[v]) {
          d[v] = d[u] + G[u][v];
          Q.push(Node(v, d[v]));
          pre[v].clear();
          pre[v].push_back(u);
        } else if (d[u] + G[u][v] == d[v]) {
          pre[v].push_back(u);
        }
      }
    }
  }
}

void DFS(int s, int v, State &minState) {
  if (s == v) {
    // 源点不需要收集，也不需要发放。
    State s(0, 0);
    for (int i = tempPath.size() - 1; i >= 0; --i) {
      int v = tempPath[i]; // 当前车站。
      int w = weight[v];
      if (w > C) {
        // 车多，收集。
        s.coll += w - C;
      } else if (w < C) {
        // 先从当前收集的车发放，不够再从总站发送。
        int need = min(s.coll, C - w);
        s.coll -= need;
        w += need;
        if (w < C) {
          s.send += C - w;
        }
      }
    }
    if (s < minState) {
      minState = s;
      // 路径不含源点。
      Path = tempPath;
    }
    return;
  }
  tempPath.push_back(v);
  for (int i = 0; i < pre[v].size(); ++i) {
    DFS(s, pre[v][i], minState);
  }
  tempPath.pop_back();
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
注意到，第二标尺并不是简单的和问题，故使用Dijkstra+DFS。
题目实际上有三个标尺：
1. 距离，最短路径。
2. 从中心发出的车数，最小。
3. 从中心收集的车数，最大。

注意，后两个标尺是互相独立的，即按照路径往下走，如果当前的站车多了，就收集，
并且前面收集的车可以给后面。如果当前站的车不够，就要给，先给当前收集的，不够就从
总站运，最后计算总站发出的和回收的车辆数，两个标尺取最小值。

注意不能简化为任意车站的车都能够互相补给，否则总站要么发车要么收车，不可能二者同时存在的。
*/

int main(int argc, char **argv) {
  fill(G[0], G[0] + MAXN * MAXN, INF);

  scanf("%d%d%d%d", &C, &N, &Sp, &M);
  C /= 2;
  for (int i = 1; i <= N; ++i) {
    scanf("%d", &weight[i]);
  }
  while (M--) {
    int i, j, t;
    scanf("%d%d%d", &i, &j, &t);
    G[i][j] = G[j][i] = t;
  }
  Dijkstra(0);
  State minState(INF, INF);
  DFS(0, Sp, minState);
  printf("%d 0", minState.send);
  for (int i = Path.size() - 1; i >= 0; --i) {
    printf("->%d", Path[i]);
  }
  printf(" %d\n", minState.coll);

  return 0;
}
