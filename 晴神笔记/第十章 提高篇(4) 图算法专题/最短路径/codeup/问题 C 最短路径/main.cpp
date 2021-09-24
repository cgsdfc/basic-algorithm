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
  // ���� 2^n MOD M.
  int ans = 1;
  while (n--) {
    ans = (2 * ans) % MOD;
  }
  return ans;
}

/*
������������
*/
struct Int {
  set<int, greater<int>> data; // ��¼����λ���Ӵ�С��
  typedef set<int, greater<int>>::iterator It;
  // ��ʼ��Ϊ�����
  void Inf() {
    data.clear();
    data.insert(INF);
  }
  // ��ʼ��Ϊ0.
  void Zero() { data.clear(); }
  friend bool operator<(const Int &a, const Int &b) {
    // �ֵ���Ƚϸ�������λ��
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
  // ����һλ��
  void Add(int b) { data.insert(b); }
  // �������ս����
  int change() {
    int ans = 0;
    if (data.size() == 1 && *data.begin() == INF) {
      return -1; // ���ɴ
    }
    for (It it = data.begin(); it != data.end(); ++it) {
      int p = Pow(*it);
      ans = (ans + p) % MOD;
    }
    return ans;
  }
};

// �ڽӱ��á�
struct Node {
  int v;
  int dis;
  Node(int _v, int _dis) : v(_v), dis(_dis) {}
};

// ���á�
struct Node2 {
  int v;
  Int dis;
  // disΪ0.
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
����Ҫ��İѱ�Ȩ��Ϊ2���ݣ�ֻ����Ȼ�����ɣ�Ȩֵ�Ĵ�С��ϵ��һ���ģ�
����������ľ����û���ˣ�Ҫ��¼·����Ȼ���ټ��������ľ��룬�ǵ�ȡģ��

����㷨����ȷ��
����һ����Ȼ������An��һ����Ȼ��X������ܴ�An�ĺ�С��X���Ƶ���2^Ai�ĺ�С��2^X������Ҳ��
��֮��Ȼ����ô�����㷨������ȷ�ġ�������ʵ�ϣ�ֻ�ܴ�An�ĺ�С��X�Ƴ�2^Ai�ĺ�С��2^X����֮�ǲ������ġ�
�����2^Ai�ĺ�С��2^X����ôAi�ĺͿ��ܴ���X��
��ʵ�ϣ��ɵȱ���͹�ʽ��0+2+...+2^(n-1)=2^n - 1 < 2^n ������Ȼ0+1+...+n-1 >
n���������ߵĴ�С��ϵ���ܻ����Ƶ��� �㷨��Ȼ�Ǵ�ġ�

��ȷ���㷨��
ע�⵽·���ı�Ȩ�ͣ���ʵ��2���ݴκͣ���2�Ķ���ʽ������ÿ�����ϵ��ֻ��ȡ0��1����Ϊ·����û���ظ��ıߣ�ÿ���ߵı�Ȩ���죩��
��������ϡ��ģ����Կ����ö���ʽ��ʾ������ʽ������ͺͱȽϴ�С��
����d�����Ԫ�ز���int�����Ƕ���ʽ��
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
      // 2���ݱ���Ϊint��
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
���Ż���Dijkstra����Դ�Ǹ�Ȩ���·��
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
