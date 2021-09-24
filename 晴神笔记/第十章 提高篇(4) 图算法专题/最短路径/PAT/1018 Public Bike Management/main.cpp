#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 505

int G[MAXN][MAXN];
int weight[MAXN]; // ��Ȩ��ĳ��վ�ж��ٳ���
int d[MAXN];
bool vis[MAXN];
int C, N, Sp, M;

const int INF = 1e9;

struct State {
  int send; // �����ǰ�ռ��ĳ��������䣬��Ҫ����վ������
  int coll; // ��ǰ�ռ��ĳ�������

  State(int s, int c) : send(s), coll(c) {}

  friend bool operator<(State a, State b) {
    if (a.send != b.send) {
      return a.send < b.send;
    }
    return a.coll < b.coll;
  }
};

// ȫ��·��������·������ʱ·����
vector<int> pre[MAXN], Path, tempPath;

struct Node {
  int v;
  int dis;
  Node(int _v, int _dis) : v(_v), dis(_dis) {}
  friend bool operator<(Node a, Node b) { return a.dis > b.dis; }
};

// �Ծ���Ϊ�����ȫ�����·����
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
      // ע�⣬ȫ��ڵ���0--N��
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
    // Դ�㲻��Ҫ�ռ���Ҳ����Ҫ���š�
    State s(0, 0);
    for (int i = tempPath.size() - 1; i >= 0; --i) {
      int v = tempPath[i]; // ��ǰ��վ��
      int w = weight[v];
      if (w > C) {
        // ���࣬�ռ���
        s.coll += w - C;
      } else if (w < C) {
        // �ȴӵ�ǰ�ռ��ĳ����ţ������ٴ���վ���͡�
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
      // ·������Դ�㡣
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
ע�⵽���ڶ���߲����Ǽ򵥵ĺ����⣬��ʹ��Dijkstra+DFS��
��Ŀʵ������������ߣ�
1. ���룬���·����
2. �����ķ����ĳ�������С��
3. �������ռ��ĳ��������

ע�⣬����������ǻ�������ģ�������·�������ߣ������ǰ��վ�����ˣ����ռ���
����ǰ���ռ��ĳ����Ը����档�����ǰվ�ĳ���������Ҫ�����ȸ���ǰ�ռ��ģ������ʹ�
��վ�ˣ���������վ�����ĺͻ��յĳ��������������ȡ��Сֵ��

ע�ⲻ�ܼ�Ϊ���⳵վ�ĳ����ܹ����ಹ����������վҪô����Ҫô�ճ��������ܶ���ͬʱ���ڵġ�
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
