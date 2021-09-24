#include <cassert>
#include <cstdio>
#include <queue>
#include <set>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
const int MOD = 100000;
const int INF = 1e9;
int N, M;

#define MAXN 105

int Pow(int n) {
  // 计算 2^n MOD M.
  int ans = 1;
  while (n--) {
    ans = (2 * ans) % MOD;
  }
  return ans;
}

/*
二进制整数。
*/
struct Int {
  set<int, greater<int>> data; // 记录非零位，从大到小。
  typedef set<int, greater<int>>::iterator It;
  // 初始化为无穷大。
  void Inf() {
    data.clear();
    data.insert(INF);
  }
  // 初始化为0.
  void Zero() { data.clear(); }
  friend bool operator<(const Int &a, const Int &b) {
    // 字典序比较各个非零位。
    It pa = a.data.begin();
    It pb = b.data.begin();
    while (pa != a.data.end() && pb != b.data.end()) {
      if (*pa != *pb) {
        return *pa < *pb;
      }
      ++pa;
      ++pb;
    }
    return pa == a.data.end() && pb != b.data.end();
  }
  // 加入一位。
  void Add(int b) { data.insert(b); }
  // 计算最终结果。
  int change() {
    int ans = 0;
    if (data.size() == 1 && *data.begin() == INF) {
      return -1; // 不可达。
    }
    for (It it = data.begin(); it != data.end(); ++it) {
      int p = Pow(*it);
      ans = (ans + p) % MOD;
    }
    return ans;
  }
};

// 邻接表用。
struct Node {
  int v;
  int dis;
  Node(int _v, int _dis) : v(_v), dis(_dis) {}
};

// 堆用。
struct Node2 {
  int v;
  Int dis;
  // dis为0.
  Node2(int _v) : v(_v) { dis.Zero(); }
  Node2(int _v, Int _dis) : v(_v), dis(_dis) {}
  friend bool operator<(const Node2 &a, const Node2 &b) {
    return b.dis < a.dis;
  }
};

vector<Node> Adj[MAXN];
Int d[MAXN];
bool vis[MAXN];

/*
不需要真的把边权设为2的幂，只有自然数即可，权值的大小关系是一样的，
但是求出来的距离就没用了，要记录路径，然后再计算真正的距离，记得取模。

这个算法不正确。
设想一个自然数数列An和一个自然数X，如果能从An的和小于X，推到出2^Ai的和小于2^X，并且也能
反之亦然，那么上述算法就是正确的。但是事实上，只能从An的和小于X推出2^Ai的和小于2^X，反之是不成立的。
即如果2^Ai的和小于2^X，那么Ai的和可能大于X。
事实上，由等比求和公式，0+2+...+2^(n-1)=2^n - 1 < 2^n ，而显然0+1+...+n-1 >
n，所以两者的大小关系不能互相推导， 算法自然是错的。

正确的算法：
注意到路径的边权和，其实是2的幂次和，即2的多项式，并且每个项的系数只能取0或1（因为路径上没有重复的边，每条边的边权互异），
并且幂是稀疏的，所以可以用多项式表示，多项式可以求和和比较大小。
所以d数组的元素不是int，而是多项式。
*/

void Dijkstra(int s) {
  for (int i = 0; i < N; ++i) {
    d[i].Inf();
    vis[i] = false;
  }
  d[s].Zero();
  priority_queue<Node2> Q;
  Q.push(Node2(s));
  while (!Q.empty()) {
    int u = Q.top().v;
    Q.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = true;
    for (int i = 0; i < Adj[u].size(); ++i) {
      int v = Adj[u][i].v;
      // 2的幂保存为int。
      int dis = Adj[u][i].dis;
      Int du = d[u];
      du.Add(dis);
      if (!vis[v] && du < d[v]) {
        d[v] = du;
        Q.push(Node2(v, du));
      }
    }
  }
}

/*
堆优化的Dijkstra，单源非负权最短路。
*/

int main(int argc, char **argv) {
  while (scanf("%d%d", &N, &M) != EOF) {
    fill(Adj, Adj + MAXN, vector<Node>());
    for (int i = 0; i < M; ++i) {
      int a, b;
      scanf("%d%d", &a, &b);
      int w = i;
      Adj[a].push_back(Node(b, w));
      Adj[b].push_back(Node(a, w));
    }
    Dijkstra(0);
    for (int i = 1; i < N; ++i) {
      int ans = d[i].change();
      printf("%d\n", ans);
    }
  }
  return 0;
}
