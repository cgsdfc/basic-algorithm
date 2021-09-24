#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1005
int N; // 节点数。
int L; // 遍历的层数限制。

// 在BFS时要记录层号，以便限制层数不超过给阈值。
struct Node {
  int v;
  int layer;
  Node(int _v, int _layer) : v(_v), layer(_layer) {}
};

vector<int> Adj[MAXN]; // 邻接表。
bool inq[MAXN];        // BFS必备。

/*
本题要求从源点s出发，限制层数不超过L的BFS所遍历到的点数（不包括s本身）。
*/
int BFS(int s) {
  queue<Node> Q;
  Q.push(Node(s, 0));
  inq[s] = true;
  int ans = 0;

  while (!Q.empty()) {
    Node top = Q.front();
    int v = top.v;
    Q.pop();
    for (int i = 0; i < Adj[v].size(); ++i) {
      int u = Adj[v][i];
      Node p(u, top.layer + 1);
      // 注意，这里的条件，
      // p的层次没有超过L，比如L=1，p是s的邻居，那么p没有超过L。
      // 并且p没有入队。
      if (p.layer <= L && !inq[p.v]) {
        ++ans;
        Q.push(p);
        inq[p.v] = true;
      }
    }
  }
  return ans;
}

int main(int argc, char **argv) {
  scanf("%d%d", &N, &L);
  // 输入每个用户的邻接表。
  // 注意，输入是逆向的，要处理。
  for (int i = 1; i <= N; ++i) {
    int k;
    scanf("%d", &k); // 关注者数量。
    while (k--) {
      int x;
      scanf("%d", &x);
      // i 关注 x，x 被i关注，转发信息从x到i。
      Adj[x].push_back(i);
    }
  }
  int K;
  scanf("%d", &K);
  while (K--) {
    int s; // 源点。
    scanf("%d", &s);
    fill(inq, inq + N + 1, false);
    int ans = BFS(s);
    printf("%d\n", ans);
  }

  return 0;
}
