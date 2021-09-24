/*
�Ͻ�˹�����㷨

����Դ��s�����нڵ����̾��룬��Դ���·��

�����ڣ�
        �Ǹ���Ȩ�����·

ʱ�临�Ӷȣ�
        �ڽӾ���O(V^2)
        �ڽӱ�O(V^2 + E)

���Ż���
        O(VlogV+E)

���ݽṹ��
        1. ��������d����¼Դ�㵽���нڵ����̾��롣
        2. �������vis����¼ĳ�ڵ��Ƿ��ѷ��ʣ������ǣ�
                1. �ѷ��ʵĽڵ㣬��̾����Ѿ�ȷ�������������Ż���
                2. �Ż�����ʱ��ֻ����δ���ʵĽڵ㡣
*/

#include <algorithm> // fill
#include <cstdio>
#include <queue> // pq
#include <vector>
using namespace std;

#define MAXN 1000 // �ڵ������ޣ�ע��ڵ��0--N-1 ��

int N; // �ڵ�����

int d[MAXN];    // �������飬��ʼ��Ϊ INF
bool vis[MAXN]; // ������飬��ʼ��Ϊ false
const int INF = 1e9;

// ��ʾһ����Ȩ�ߡ�
struct Node {
  int v;    // �յ㡣
  int dist; // ��Ȩ��
  Node(int v_, int dist_) {
    v = v_;
    dist = dist_;
  }
};

// ע���ڽӱ�Ҫ���ϱ�Ȩ��
vector<Node> Adj[MAXN]; // �ڽӱ�

/*
�ڽӱ�汾�Ͻ�˹����
�������鼴Ϊ��������㷨�ܴ�������ͼ������ͼҲ����ͨ�����ر߷���ת��Ϊ����ͼ��
s��Դ�㡣
*/

void Dijkstra(int s) {
  // ��ʼ����
  fill(d, d + N, INF);       // ���������
  fill(vis, vis + N, false); // �ڵ�δ���ʡ�
  d[s] = 0; // ע�⣬�������©������û�����ѭ��ֻ����һ����

  for (int i = 0; i < N; ++i) { // ѭ��N�֣�ÿ�ֽ��һ���ڵ㡣
    // ���ҵ�ǰ���Žڵ㡣
    int u = -1;
    int MIN = INF;
    // ����ɨ�裬������Ҳ���С��INF�Ľڵ㣬��˵��ʣ�½ڵ�ȫ�����ɴ
    for (int j = 0; j < N; ++j) {
      if (!vis[j] && d[j] < MIN) {
        // ע���ѷ��ʽڵ㲻Ҫ���ǡ�
        u = j;
        MIN = d[j];
      }
    }
    if (u == -1) {
      // �����ڱ�INF���ŵĽڵ㣬���Բ����ܼ����Ż���
      return;
    }
    // �ҵ���ǰ���Žڵ�u������̰�Ĳ��ԣ�u����ȫ�����Ž⡣
    vis[u] = true;
    // ����u�����Ż�����ͨ��uΪ�м�ڵ㣬�Ż�����δ���ʽڵ��d��
    // ʵ����Ҫ����Ľڵ����u���ھӡ�������u���ھӡ�
    for (int j = 0; j < N; ++j) {
      int v = Adj[u][j].v;
      int dist = Adj[u][j].dist;
      if (!vis[v] && d[u] + dist < d[v]) {
        // ���ڸ��Ž⡣
        d[v] = d[u] + dist;
      }
    }
  }
}

// �ڽӾ��󣬱����Ȩ������INF������߲����ڡ�
// ע�⽨ͼʱ��Ҫʹ�߲����ڵľ���Ԫ��ΪINF����fill��
int G[MAXN][MAXN];

/*
�ڽӾ����Dijkstra��
Ψһ���������Ż������ı����ھӲ��֡�
*/
void Dijkstra2(int s) {
  fill(d, d + N, INF);
  fill(vis, vis + N, false);
  d[s] = 0;
  for (int i = 0; i < N; ++i) {
    int u = -1;
    int MIN = INF;
    for (int j = 0; j < N; ++j) {
      if (!vis[j] && d[j] < MIN) {
        u = j;
        MIN = d[j];
      }
    }
    if (u == -1) {
      return;
    }
    // u����̾�����ǰ���ֲ�����ֻ������һ�ֲ���ȷ��u����̾��벻���ٱ仯�ˡ�
    // Ҳ����˵��ÿ�ֵ���̾������Сֵ���������ٸ����ˣ���˾Ͷ������ˡ�
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      if (!vis[v] && G[u][v] != INF && G[u][v] + d[u] < d[v]) {
        d[v] = G[u][v] + d[u];
      }
    }
  }
}

/*
���Ż���Dijkstra���ڽӱ�汾

ע����Ż���ԭ���汾���޸ģ�
1. �ѵ�Ԫ�����ͣ����뽨���ڵ������̾������ϵ������Node��
2. �ѵıȽϺ�����ʹС�ľ����ȳ��ӡ�
3. �Ż�����ʱ�ԶѵĲ�����
*/

struct cmp {
  bool operator()(Node a, Node b) {
    return a.dist > b.dist; // С���ѡ�
  }
};

typedef priority_queue<Node, vector<Node>, cmp> PQueue;

/*
ע��ѵĴ���
*/
void Dijkstra3(int s) {
  PQueue Q;
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  d[s] = 0;
  Q.push(Node(s, 0));

  // ������BFS��д������˳�֡�
  while (!Q.empty()) {
    Node top = Q.top();
    Q.pop();
    if (vis[top.v]) {
      continue;
      // �Ǹ�����Ԫ�أ���Ϊ���ŵľ��뱻�����ˣ������Ϊ�ѷ��ʣ����ɵĽ��޷��Ӷ���ɾ����
      // ע�⣬��������Ԫ�����޷�����ġ�
    }
    // ���Q��Ϊ�ն��Ҳ���v�����㷨����������Ҫ���С�
    int v = top.v;
    vis[v] = true;
    // �Ż����������Ż��Ľڵ�Ҫ����ѣ����򲻻ᱻ�㷨���ǣ���
    for (int i = 0; i < Adj[v].size(); ++i) {
      int u = Adj[v][i].v;
      int dist = Adj[v][i].dist;
      // ����v��·��������
      if (!vis[u] && d[v] + dist < d[u]) {
        d[u] = d[v] + dist;
        // ע�⣬�Ѹ��ŵľ���ֱ�Ӽ���ѣ������Ž���Ӻ�
        // vis��Ϊtrue����������ͬ�ڵ�ľ���Ľڵ㣬�ͻᱻ���Ե���
        Q.push(Node(u, d[u]));
      }
    }
  }
}

/*
���Ż����ڽӾ���
*/
void Dijkstra4(int s) {
  // ��ʼ����
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      // ����һ��INF�����Է�ֹ�����
      if (!vis[v] && G[u][v] != INF && G[u][v] + d[u] < d[v]) {
        d[v] = G[u][v] + d[u];
        Q.push(Node(v, d[v]));
      }
    }
  }
}

/*
��¼���·����

ĳ���ڵ���ܴ��ڶ������·����
����1��ÿ���ڵ��¼�������·����ǰ������ά��int����pre��
����pre�������һ�����·��������С�������������˷�ֻ�ܵõ�����һ��
���·����

����2�����Եõ�ȫ�������·������ÿ���ڵ��¼���ڶ������·����ǰ������ά��vector<int>����pre��
�����������·��ͼ�����·��ͼ���ǰ��������нڵ�����·����ͼ����Ȼ���޻��ģ�����л�����
�߻���·����Ȼ�����������������·������

�Զ��Ż����ڽӾ���汾Ϊ���ӣ�ʵ���ϣ�ֻ��Ҫ���Ż���������ά��pre���鼴�ɡ�
����1��2ά���ķ�����ͬ��
*/

/*
����ÿ���ڵ��ĳ�����·����
*/
int pre[MAXN];

void Dijkstra5(int s) {
  // ��ʼ����
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  /*
  pre�ĳ�ʼ���������Ԫ��Ϊi����ʾÿ��ǰ��Ϊ������
  ���ͼ����ͨͼ�������pre��һ������s��Ψһ�ĸ���ֻ��sʹ��
  pre[s]=s�����ڴ�ӡ·�����á�
  */
  for (int i = 0; i < N; ++i) {
    pre[i] = i;
  }

  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      // ����һ��INF�����Է�ֹ�����
      if (!vis[v] && G[u][v] != INF && G[u][v] + d[u] < d[v]) {
        d[v] = G[u][v] + d[u];
        Q.push(Node(v, d[v]));
        /*
        pre�ĸ��¡�
        */
        pre[v] = u; // ���Ż���v��ǰ���ǵ�ǰ���Ž�u��
      }
    }
  }
}

/*
�ݹ��ӡ���·����
s��Դ�㡣
v���յ㡣����ǰ�ڵ㣩
*/
void PrintPath(int s, int v) {
  if (s == v) {
    printf("%d\n", s);
    return;
  }
  // �ȴ�ӡ���ڵ��·����
  PrintPath(s, pre[v]);
  printf("%d\n", v);
}

/*
����ÿ���ڵ��ȫ�����·����
pre2��Ԫ�ش�ŵ���ĳ�ڵ��ȫ��ǰ����
*/
vector<int> pre2[MAXN];

void Dijkstra6(int s) {
  // ��ʼ����
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  /*
  ע�⣬�����ʼ����vector�Զ���ʼ��Ϊ�ա�
  */

  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      // ����һ��INF�����Է�ֹ�����
      if (!vis[v] && G[u][v] != INF) {
        // ע�⣬����pre�󣬵��ڵ�ǰ���Ž�����ҲҪ����
        if (G[u][v] + d[u] < d[v]) {
          d[v] = G[u][v] + d[u];
          Q.push(Node(v, d[v]));
          // ��ǰ�Ǹ��Ž⣬֮ǰ�ռ���ǰ��û���ˡ�
          pre2[v].clear();
          // ������߼�������һ�߼������ֵ��һ�߼�¼�ﵽ���ֵ��ԭ����߼���
          pre2[v].push_back(u);
        } else if (G[u][v] + d[u] == d[v]) {
          // ��ͬ���ȵ�·���ֶ���һ����Ҫ����һ��ǰ����
          pre2[v].push_back(u);
        }
      }
    }
  }
}

vector<int> tempPath;

/*
�ݹ��ӡ·����
�����·��������������Ҫ�󣬿��Զ�pre��ÿһ��vector�������򣬶�����
��ȫ��·���洢��������ÿ��·���������ʽ�Ǵ�Դ�㵽�յ�Ľڵ����У��ո�ָ���
*/
void PrintPath2(int s, int v) {
  if (s == v) {
    // sΪ��㣬�����˵ݹ�߽硣
    tempPath.push_back(s);
    // ��ӡ·����ע�⣬tempPath���򱣴�·����Ҫ���������
    for (int i = tempPath.size() - 1; i >= 0; --i) {
      printf("%d%s", tempPath[i], i == 0 ? "\n" : " ");
    }
    tempPath.pop_back();
    return;
  }
  tempPath.push_back(v);
  for (int i = 0; i < pre2[v].size(); ++i) {
    PrintPath2(s, pre2[v][i]);
  }
  tempPath.pop_back();
}

/*
�ڶ�������⡣

������̵�·�������ж�������Ҫʹ��Ψһ����Ŀ��������ڶ���ߣ������¼��֣�
1. ������Ȩ��Ҫ��·���ı�Ȩ����С��
2. ������Ȩ��Ҫ��·���ĵ�Ȩ����С��
3. ͳ�����·�����������������Ҫ�������·���Ļ����ǲ���Ҫʹ��vector�ġ�
*/

/*
������Ȩ��

ע�⵽���·�����Ȿ��������Ȩ����С��·�������������µ�һ���Ȩ����ȫ���Ƶġ�
���ȣ���Ҫ��¼��Ŀ����ı�Ȩ������Ԫ��(u,v,c)����u����v�ıߣ������Ȩc�������ö�ά����cost��ʾ��
Ȼ����Ⱦ�������d��������������c����ʾԴ�㵽u��·������С��Ȩ�͡�
����Ƕ��㷨���޸ģ�
1. ��ʼ�����������ݽṹ��
2. �޸��Ż��������߼���ͬ����������c��
*/

int cost[MAXN][MAXN]; // ��Ŀ�������ݣ�cost[u][v] ����� u->v �ı�Ȩ��
int c[MAXN]; // ����Դ�㵽u����С���ѣ���Ȩ�ͣ�����d����һ����¡�

// �������Ҫ��С���±�Ȩcost��
void Dijkstra7(int s) {
  // ��ʼ����
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  fill(c, c + N, INF);
  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;
  c[s] = 0;

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      if (!vis[v] && G[u][v] != INF) {
        // ����һ��߳��ָ���ʱ��ͬʱ����������ߵĵ�ǰ���ţ���d��c��
        if (G[u][v] + d[u] < d[v]) {
          d[v] = G[u][v] + d[u];
          c[v] = cost[u][v] + c[u];
          // ע��d��c�ĸ�������ȫ���Ƶġ�
          Q.push(Node(v, d[v]));
          // ����һ��ߺ͵�ǰ������ͬʱ�����ǵڶ���߲����¡�
        } else if (G[u][v] + d[u] == d[v] && cost[u][v] + c[u] < c[v]) {
          // ��ʱֻ����µڶ���ߡ�
          c[v] = cost[u][v] + c[u];
        }
      }
    }
  }
}

/*
������Ȩ��

������ĿҪ�������·���Ļ����ϣ�Ҫ��·���Ľڵ��Ȩ����󣨱���˵ÿ��������Щ���ʣ�Ҫʹ���ռ���
������󣩡���Ȩ����Ŀ���룬��¼������weight�У���������w����ʾԴ��s���ڵ�u��·��������Ȩ�ͣ�
���¹�����������Ȩ�����Ƶģ����ȿ��ǵ�һ��ߣ����룩��Ȼ���ǵڶ���ߡ�ע��������Ȩ��д�����в�ͬ��
*/
int weight[MAXN]; // ��Ŀ���롣
int w[MAXN]; // Դ��s���ڵ�u��·��������Ȩ�͡�����ǰs��u������Ȩ�͡�

void Dijkstra8(int s) {
  // ��ʼ����
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  fill(w, w + N,
       0); // ����Сʱ����ʼʱΪINF�������ʱ����ʼʱΪ0���Ǹ����������С����

  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;
  w[s] = weight[s];

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      if (!vis[v] && G[u][v] != INF) {
        if (G[u][v] + d[u] < d[v]) {
          d[v] = G[u][v] + d[u];
          // s->u, u->v = s->v
          w[v] = weight[v] + w[u];

          Q.push(Node(v, d[v]));
          // ����һ��ߺ͵�ǰ������ͬʱ�����ǵڶ���߲����¡�
        } else if (G[u][v] + d[u] == d[v] && weight[v] + w[u] > w[v]) {
          // ��ʱֻ����µڶ���ߡ�
          w[v] = weight[v] + w[u];
        }
      }
    }
  }
}

/*
�����·��������
����num���飬��ʾs��u�����·�����������¹������ȫ�����·�����ơ�
*/
int num[MAXN];

void Dijkstra9(int s) {
  // ��ʼ����
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  fill(num, num + N, 0);

  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;
  num[s] = 1; // ע�⣬��Դ��s�����·���ҽ���һ����

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      if (!vis[v] && G[u][v] != INF) {
        if (G[u][v] + d[u] < d[v]) {
          d[v] = G[u][v] + d[u];
          num[v] = num[u]; // ��Ϊ����u��·�����̣�����֮ǰ�����v�����·
                           // ����������ˣ���������ġ�
        } else if (G[u][v] + d[u] == d[v]) {
          // ����u��·����v�ĵ�ǰ���·��һ�����������ۼӡ�
          num[v] += num[u];
        }
      }
    }
  }
}
