#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

#define MAXN 30

struct Node {
  int v, w;
  Node(int vv, int ww) : v(vv), w(ww) {}
};

vector<Node> Adj[MAXN];
stack<int> topOrder; // 拓扑序列。
int In[MAXN];        // 入度。
int ve[MAXN], vl[MAXN];

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, M;
int Q;

int charToInt[130];
char IntToChar[MAXN];
int Next[MAXN]; // 关键路径。
int S, T;       // 源点，汇点。

bool TopoSort() {
  queue<int> Q;
  topOrder = stack<int>();
  memset(ve, 0, sizeof(ve));

  for (int v = 1; v <= N; ++v) {
    if (!In[v]) {
      S = v; // 入度为0是源点。
      Q.push(v);
    }
  }
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    topOrder.push(u);
    // 更新后继的ve。
    for (int i = 0; i < Adj[u].size(); ++i) {
      int v = Adj[u][i].v;
      int w = Adj[u][i].w;
      --In[v];
      if (!In[v]) {
        Q.push(v);
      }
      if (ve[u] + w > ve[v]) {
        ve[v] = ve[u] + w;
      }
    }
  }
  return topOrder.size() == N;
}

void CriticalPath() {
  if (!TopoSort()) {
    return; // 题目保证是dag。
  }
  int maxLen = 0; // 关键路径长度。
  for (int i = 1; i <= N; ++i) {
    if (ve[i] > maxLen) {
      maxLen = ve[i];
      T = i; // 汇点的ve就是关键路径长度。
    }
  }
  fill(vl, vl + MAXN, maxLen);
  // 求vl。
  while (!topOrder.empty()) {
    int u = topOrder.top();
    topOrder.pop();
    for (int i = 0; i < Adj[u].size(); ++i) {
      int v = Adj[u][i].v;
      int w = Adj[u][i].w;
      if (vl[v] - w < vl[u]) {
        vl[u] = vl[v] - w;
      }
    }
  }
  for (int v = 1; v <= N; ++v) {
    Next[v] = -1;
  }
  // 求所以边的e，l。
  for (int v = 1; v <= N; ++v) {
    for (int i = 0; i < Adj[v].size(); ++i) {
      int u = Adj[v][i].v;
      int w = Adj[v][i].w;
      int e = ve[v];
      int l = vl[u] - w;
      if (e == l) {
        // 题目只要输出一条关键路径，说明路径唯一。
        Next[v] = u;
      }
    }
  }
  int v = S;
  while (v != T) {
    printf("(%c,%c) ", IntToChar[v], IntToChar[Next[v]]);
    v = Next[v];
  }
  printf("%d\n", maxLen);
}

int main(int argc, char **argv) {
  while (scanf("%d", &Q) != EOF) {
    while (Q--) {
      memset(charToInt, 0, sizeof(charToInt));
      memset(IntToChar, 0, sizeof(IntToChar));
      memset(In, 0, sizeof(In));
      fill(Adj, Adj + MAXN, vector<Node>());

      scanf("%d%d", &N, &M);
      // 顶点集。
      getchar();
      for (int i = 1; i <= N; ++i) {
        int c = getchar();
        charToInt[c] = i;
        IntToChar[i] = c;
      }
      while (M--) {
        char u, v;
        int w;
        getchar();
        scanf("%c %c %d", &u, &v, &w);
        u = charToInt[u];
        v = charToInt[v];
        // 有向图：u->v
        Adj[u].push_back(Node(v, w));
        In[v]++;
      }

      CriticalPath();
    }
  }
  return 0;
}
