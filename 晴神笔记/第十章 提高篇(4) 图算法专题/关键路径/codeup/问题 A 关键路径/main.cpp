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
stack<int> topOrder; // �������С�
int In[MAXN];        // ��ȡ�
int ve[MAXN], vl[MAXN];

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, M;
int Q;

int charToInt[130];
char IntToChar[MAXN];
int Next[MAXN]; // �ؼ�·����
int S, T;       // Դ�㣬��㡣

bool TopoSort() {
  queue<int> Q;
  topOrder = stack<int>();
  memset(ve, 0, sizeof(ve));

  for (int v = 1; v <= N; ++v) {
    if (!In[v]) {
      S = v; // ���Ϊ0��Դ�㡣
      Q.push(v);
    }
  }
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    topOrder.push(u);
    // ���º�̵�ve��
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
    return; // ��Ŀ��֤��dag��
  }
  int maxLen = 0; // �ؼ�·�����ȡ�
  for (int i = 1; i <= N; ++i) {
    if (ve[i] > maxLen) {
      maxLen = ve[i];
      T = i; // ����ve���ǹؼ�·�����ȡ�
    }
  }
  fill(vl, vl + MAXN, maxLen);
  // ��vl��
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
  // �����Աߵ�e��l��
  for (int v = 1; v <= N; ++v) {
    for (int i = 0; i < Adj[v].size(); ++i) {
      int u = Adj[v][i].v;
      int w = Adj[v][i].w;
      int e = ve[v];
      int l = vl[u] - w;
      if (e == l) {
        // ��ĿֻҪ���һ���ؼ�·����˵��·��Ψһ��
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
      // ���㼯��
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
        // ����ͼ��u->v
        Adj[u].push_back(Node(v, w));
        In[v]++;
      }

      CriticalPath();
    }
  }
  return 0;
}
