#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, M, S, D; // 点数，边数，起点，终点。
const int INF = 1e9;

#define MAXN 505

int G[MAXN][MAXN];
int cost[MAXN][MAXN];
int d[MAXN];
int c[MAXN]; // 边权和。
bool vis[MAXN];

vector<int> pre[MAXN];
vector<int> tempPath, Path;
int pre2[MAXN];

/*
本题要求最短路径，第二标尺为边权和，要输出路径，最小距离和边权和。
因为第二标尺为“和”，可以不需要DFS。
用Dijkstra+DFS和堆优化求解。
*/

struct Node {
  int v;
  int dist;
  Node(int v_, int dist_) {
    v = v_;
    dist = dist_;
  }
  bool operator<(Node a) const { return dist > a.dist; }
};

// 专心求解最短路径。
void Dijkstra(int s) {
  priority_queue<Node> Q;
  fill(d, d + N, INF);
  fill(vis, vis + N, false);

  Q.push(Node(s, 0));
  d[s] = 0;
  while (!Q.empty()) {
    Node top = Q.top();
    Q.pop();
    int u = top.v;
    if (vis[u]) {
      continue;
    }
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      if (!vis[v] && G[u][v] != INF) {
        if (d[u] + G[u][v] < d[v]) {
          d[v] = d[u] + G[u][v];
          pre[v].clear();
          pre[v].push_back(u);
          Q.push(Node(v, d[v]));
        } else if (d[u] + G[u][v] == d[v]) {
          pre[v].push_back(u);
        }
      }
    }
  }
}

/*
单Dijkstra解法，不需要DFS。
*/
void Dijkstra2(int s) {
  fill(d, d + N, INF);
  fill(c, c + N, INF);
  fill(vis, vis + N, false); // Dij需要vis，每次搞一个节点。
  priority_queue<Node> Q;
  Q.push(Node(s, 0));
  d[s] = 0;
  c[s] = 0; // 要同步更新c，就要先初始化。
  // 唯一路径的情况，必须初始化pre数组。
  for (int i = 0; i < N; ++i) {
    pre2[i] = i;
  }

  // 注意vis不要初始化！不要初始化！不要初始化！
  while (!Q.empty()) {
    int u = Q.top().v;
    // 注意：这里Node的dist是用来给Q排序的，等于d[u].
    Q.pop();
    // 注意判重。
    if (vis[u])
      continue;
    vis[u] = true;
    // 松弛。
    for (int v = 0; v < N; ++v) {
      if (vis[v] || G[u][v] == INF) {
        continue;
      }
      // 一样的松弛条件。
      if ((d[u] + G[u][v] < d[v]) ||
          (d[u] + G[u][v] == d[v] && c[u] + cost[u][v] < c[v])) {
        d[v] = d[u] + G[u][v];
        c[v] = c[u] + cost[u][v];
        pre2[v] = u;
        Q.push(Node(v, d[v]));
      }
    }
  }
}

void DFS(int s, int v, int &minCost) {
  // 注意，pre[s].empty()==true。即源点没有前驱。
  if (s == v) {
    tempPath.push_back(v);
    // 求边权和。
    int ans = 0;
    for (int i = tempPath.size() - 1; i > 0; --i) {
      int u = tempPath[i];
      int v = tempPath[i - 1];
      ans += cost[u][v];
    }
    if (ans < minCost) {
      minCost = ans;
      Path = tempPath;
    }
    tempPath.pop_back();
    return;
  }
  tempPath.push_back(v);
  for (int i = 0; i < pre[v].size(); ++i) {
    DFS(s, pre[v][i], minCost);
  }
  tempPath.pop_back();
}

bool inq[MAXN];
vector<Node> Adj[MAXN];

/*
Bellman实现。
*/
void Bellman(int s) {
  fill(d, d + N, INF);
  fill(c, c + N, INF);
  d[s] = 0;
  c[s] = 0;
  // 唯一路径的情况，必须初始化pre数组。
  for (int i = 0; i < N; ++i) {
    pre2[i] = i;
  }

  int T = N - 1; // 松弛轮数。
  while (T--) {
    // 每轮遍历所有边。
    for (int u = 0; u < N; ++u) {
      for (int i = 0; i < Adj[u].size(); ++i) {
        int v = Adj[u][i].v;
        int dis = Adj[u][i].dist;
        if ((d[u] + dis < d[v]) ||
            (d[u] + dis == d[v] && c[u] + cost[u][v] < c[v])) {
          // 松弛。
          d[v] = d[u] + dis;
          c[v] = c[u] + cost[u][v];
          pre2[v] = u;
        }
      }
    }
  }
}

/*
本题要求在两个标尺下最优的唯一最短路径，已经两个标尺的最优值。
*/
void SPFA(int s) {
  fill(inq, inq + N, false);
  fill(d, d + N, INF);
  fill(c, c + N, INF);
  for (int i = 0; i < N; ++i) {
    pre2[i] = i;
  }
  d[s] = 0;
  c[s] = 0;
  queue<int> Q;
  Q.push(s);
  inq[s] = true;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    inq[u] = false;
    for (int i = 0; i < Adj[u].size(); ++i) {
      int v = Adj[u][i].v;
      int dis = Adj[u][i].dist;
      // 把第一标尺和第二标尺的两个分支合并，因为没有要求路径数目或者全部路径，
      // 所以是可以合并的。否则，更新的逻辑可能不相同。比如路径数目是要求第一标尺最优的路径数目，
      // 不考虑第二标尺的，那么就必须区分第一标尺不变或者更优的情况。
      if ((d[u] + dis < d[v]) ||
          (d[u] + dis == d[v] && c[u] + cost[u][v] < c[v])) {
        // 同时更新两个标尺。
        d[v] = d[u] + dis;
        c[v] = c[u] + cost[u][v];
        pre2[v] = u;
        if (!inq[v]) {
          Q.push(v);
          inq[v] = true;
        }
      }
    }
  }
}

// 递归打印路径，最后可以多一个空格。
void PrintPath(int s, int v) {
  if (s == v) {
    printf("%d ", s);
    return;
  }
  PrintPath(s, pre2[v]);
  printf("%d ", v);
}

int main(int argc, char **argv) {
  scanf("%d%d%d%d", &N, &M, &S, &D);
  // 注意一定要填满整个二维数组。
  fill(G[0], G[0] + MAXN * MAXN, INF);

  /*
  图的存储如果不统一，则更换算法时容易出错，
  建议统一使用邻接表。
  */

  while (M--) {
    int u, v, d, c;
    scanf("%d%d%d%d", &u, &v, &d, &c);
    G[u][v] = G[v][u] = d;
    //		Adj[u].push_back(Node(v, d));
    //		Adj[v].push_back(Node(u, d));
    cost[u][v] = cost[v][u] = c;
    // 无向图。
  }

  //	Bellman(S);
  Dijkstra2(S);
  //	SPFA(S);
  PrintPath(S, D);
  printf("%d %d\n", d[D], c[D]);

  //	Dijkstra(S);
  //	int minCost=INF;
  //	DFS(S, D, minCost);
  //	for (int i=Path.size()-1;i>=0;--i) {
  //		printf("%d ", Path[i]);
  //	}
  //	printf("%d %d\n", d[D], minCost);
  //
  return 0;
}
