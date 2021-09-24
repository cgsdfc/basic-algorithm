#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, M, S, D; // ��������������㣬�յ㡣
const int INF = 1e9;

#define MAXN 505

int G[MAXN][MAXN];
int cost[MAXN][MAXN];
int d[MAXN];
int c[MAXN]; // ��Ȩ�͡�
bool vis[MAXN];

vector<int> pre[MAXN];
vector<int> tempPath, Path;
int pre2[MAXN];

/*
����Ҫ�����·�����ڶ����Ϊ��Ȩ�ͣ�Ҫ���·������С����ͱ�Ȩ�͡�
��Ϊ�ڶ����Ϊ���͡������Բ���ҪDFS��
��Dijkstra+DFS�Ͷ��Ż���⡣
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

// ר��������·����
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
��Dijkstra�ⷨ������ҪDFS��
*/
void Dijkstra2(int s) {
  fill(d, d + N, INF);
  fill(c, c + N, INF);
  fill(vis, vis + N, false); // Dij��Ҫvis��ÿ�θ�һ���ڵ㡣
  priority_queue<Node> Q;
  Q.push(Node(s, 0));
  d[s] = 0;
  c[s] = 0; // Ҫͬ������c����Ҫ�ȳ�ʼ����
  // Ψһ·��������������ʼ��pre���顣
  for (int i = 0; i < N; ++i) {
    pre2[i] = i;
  }

  // ע��vis��Ҫ��ʼ������Ҫ��ʼ������Ҫ��ʼ����
  while (!Q.empty()) {
    int u = Q.top().v;
    // ע�⣺����Node��dist��������Q����ģ�����d[u].
    Q.pop();
    // ע�����ء�
    if (vis[u])
      continue;
    vis[u] = true;
    // �ɳڡ�
    for (int v = 0; v < N; ++v) {
      if (vis[v] || G[u][v] == INF) {
        continue;
      }
      // һ�����ɳ�������
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
  // ע�⣬pre[s].empty()==true����Դ��û��ǰ����
  if (s == v) {
    tempPath.push_back(v);
    // ���Ȩ�͡�
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
Bellmanʵ�֡�
*/
void Bellman(int s) {
  fill(d, d + N, INF);
  fill(c, c + N, INF);
  d[s] = 0;
  c[s] = 0;
  // Ψһ·��������������ʼ��pre���顣
  for (int i = 0; i < N; ++i) {
    pre2[i] = i;
  }

  int T = N - 1; // �ɳ�������
  while (T--) {
    // ÿ�ֱ������бߡ�
    for (int u = 0; u < N; ++u) {
      for (int i = 0; i < Adj[u].size(); ++i) {
        int v = Adj[u][i].v;
        int dis = Adj[u][i].dist;
        if ((d[u] + dis < d[v]) ||
            (d[u] + dis == d[v] && c[u] + cost[u][v] < c[v])) {
          // �ɳڡ�
          d[v] = d[u] + dis;
          c[v] = c[u] + cost[u][v];
          pre2[v] = u;
        }
      }
    }
  }
}

/*
����Ҫ����������������ŵ�Ψһ���·�����Ѿ�������ߵ�����ֵ��
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
      // �ѵ�һ��ߺ͵ڶ���ߵ�������֧�ϲ�����Ϊû��Ҫ��·����Ŀ����ȫ��·����
      // �����ǿ��Ժϲ��ġ����򣬸��µ��߼����ܲ���ͬ������·����Ŀ��Ҫ���һ������ŵ�·����Ŀ��
      // �����ǵڶ���ߵģ���ô�ͱ������ֵ�һ��߲�����߸��ŵ������
      if ((d[u] + dis < d[v]) ||
          (d[u] + dis == d[v] && c[u] + cost[u][v] < c[v])) {
        // ͬʱ����������ߡ�
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

// �ݹ��ӡ·���������Զ�һ���ո�
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
  // ע��һ��Ҫ����������ά���顣
  fill(G[0], G[0] + MAXN * MAXN, INF);

  /*
  ͼ�Ĵ洢�����ͳһ��������㷨ʱ���׳���
  ����ͳһʹ���ڽӱ�
  */

  while (M--) {
    int u, v, d, c;
    scanf("%d%d%d%d", &u, &v, &d, &c);
    G[u][v] = G[v][u] = d;
    //		Adj[u].push_back(Node(v, d));
    //		Adj[v].push_back(Node(u, d));
    cost[u][v] = cost[v][u] = c;
    // ����ͼ��
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
