#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int INF = 1e9;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
用回溯法解最短路径的题目，
会更慢，但是不妨试一试。
*/

struct State {
  int dis, cost;
  friend bool operator<(State a, State b) {
    if (a.dis != b.dis)
      return a.dis < b.dis;
    return a.cost < b.cost;
  }
  State() {}
  State(int dd, int cc) : dis(dd), cost(cc) {}
};

#define MAXN 1005
int N, M;
int S, T;

bool vis[MAXN];
State G[MAXN][MAXN];

void DFS(int s, int v, State now, State &ans) {
  if (s == v) {
    if (now < ans) {
      ans = now;
    }
    return;
  }
  vis[s] = true;
  for (int u = 1; u <= N; ++u) {
    if (G[s][u].dis != INF && !vis[u]) {
      State next = now;
      next.dis += G[s][u].dis;
      next.cost += G[s][u].cost;
      DFS(u, v, next, ans);
    }
  }
  vis[s] = false;
}

int main(int argc, char **argv) {
  while (scanf("%d%d", &N, &M), (N || M)) {
    fill(G[0], G[0] + MAXN * MAXN, State(INF, INF));
    fill(vis, vis + MAXN, false);

    while (M--) {
      int a, b;
      State s;
      scanf("%d%d%d%d", &a, &b, &s.dis, &s.cost);
      /*
      重边的处理：
      取最小的那一条即可。
      */
      s = min(s, G[a][b]);
      G[a][b] = G[b][a] = s;
    }
    scanf("%d%d", &S, &T);
    State now(0, 0);
    State ans(INF, INF);
    DFS(S, T, now, ans);
    printf("%d %d\n", ans.dis, ans.cost);
  }

  return 0;
}
