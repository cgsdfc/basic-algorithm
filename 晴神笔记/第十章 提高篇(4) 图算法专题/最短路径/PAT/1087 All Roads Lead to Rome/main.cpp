#include <algorithm>
#include <iostream> // �漰string��ʱ���ʺ���iostream��
#include <map>
#include <queue>
#include <string>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 205 // �ڵ�����

int weight[MAXN];  // ��Ȩ��
int G[MAXN][MAXN]; // ��Ȩ��
const int INF = 1e9;

map<string, int> StringToInt;
string IntToString[MAXN];
int index;

int Map(string &name) {
  if (StringToInt.count(name)) {
    return StringToInt[name];
  } else {
    StringToInt[name] = index;
    IntToString[index] = name;
    return index++;
  }
}

int N, K; // �ڵ�����������
string start;
string End = "ROM";
int S; // Դ�㡣
int D; // �յ㡣

bool vis[MAXN];
vector<int> pre[MAXN], tempPath, Path;
int d[MAXN];   // ��С��Ȩ�͡�
int num[MAXN]; // cost ��С��·��������

struct Node {
  int v, dis;
  Node(int _v, int _d) : v(_v), dis(_d) {}
  friend bool operator<(Node a, Node b) { return a.dis > b.dis; }
};

/*
Dijkstra+DFS�ĺ�����Ҫ��Dijkstra��ü򵥣�רע�����
���·����
*/
void Dijkstra(int s) {
  priority_queue<Node> Q;
  fill(vis, vis + MAXN, false);
  fill(d, d + MAXN, INF);
  d[s] = 0;
  num[s] = 1;
  Q.push(Node(s, 0));
  while (!Q.empty()) {
    int u = Q.top().v;
    Q.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      if (!vis[v] && G[u][v] != INF) {
        if (d[u] + G[u][v] < d[v]) {
          d[v] = d[u] + G[u][v];
          pre[v].clear();
          pre[v].push_back(u);
          num[v] = num[u];
          Q.push(Node(v, d[v]));
        } else if (d[u] + G[u][v] == d[v]) {
          num[v] += num[u];
          pre[v].push_back(u);
        }
      }
    }
  }
}

/*
��·��ƽ���������·����
��Ϊ��Щ·��������̵ģ����ҵ�Ȩ�Ͷ���󣬼���Ȩ�Ͷ���һ���ģ�
�󳤶���С�ļ��ɡ�
*/
void DFS(int s, int v, int &maxSum, int &minLen) {
  if (s == v) {
    int sum = 0;
    for (int i = 0; i < tempPath.size(); ++i) {
      int v = tempPath[i];
      sum += weight[v];
    }
    int len = tempPath.size();
    if (sum > maxSum || (sum == maxSum && len < minLen)) {
      maxSum = sum;
      minLen = len;
      Path = tempPath;
    }
    return;
  }
  tempPath.push_back(v);
  for (int i = 0; i < pre[v].size(); ++i) {
    DFS(s, pre[v][i], maxSum, minLen);
  }
  tempPath.pop_back();
}

int main(int argc, char **argv) {
  //	cout.sync_with_stdio(false);

  fill(G[0], G[0] + MAXN * MAXN, INF);
  cin >> N >> K >> start;
  S = Map(start);
  D = Map(End);

  for (int i = 0; i < N - 1; ++i) {
    string name;
    int w;
    cin >> name >> w;
    int v = Map(name);
    weight[v] = w;
  }

  for (int i = 0; i < K; ++i) {
    string s1, s2;
    int cost;
    cin >> s1 >> s2 >> cost;
    int u = Map(s1);
    int v = Map(s2);
    // ����ͼ��
    G[u][v] = G[v][u] = cost;
  }
  Dijkstra(S);
  int maxSum = -INF;
  int minLen = INF;
  DFS(S, D, maxSum, minLen);
  printf("%d %d %d %d\n", num[D], d[D], maxSum, maxSum / minLen);
  printf("%s", start.c_str());
  for (int i = Path.size() - 1; i >= 0; --i) {
    int v = Path[i];
    string &name = IntToString[v];
    printf("->%s", name.c_str());
  }
  printf("\n");

  return 0;
}
