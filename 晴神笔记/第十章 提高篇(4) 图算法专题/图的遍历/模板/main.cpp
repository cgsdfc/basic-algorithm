#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

// �����ڽӾ����Ǳ߲����ڡ�
// G[i][j]=INF ��ʾ i��jû�бߡ�
const int INF = 1000000000;

/*
ͼDFS����ģ�塣
һЩ��ģ�⣬���硶������������������������DFSģ�壬��ȷ��
һ������������˶�������ˡ�DFS�������ж�ͼ�Ƿ��л���
*/

#define MAXN 100

int N; // �ڵ�����

// �ڵ�ı�ſ�������Ŀ������Ҳ�������Լ�ת��������������Ŀ�������ַ�������map
// ת��Ϊint���±���ܴ�0����1��ʼ��
bool vis[MAXN];

int G[MAXN][MAXN]; // �ڽӾ���

// ����u���ڵ���ͨ������нڵ㣨����ͼ����ͨ����������ͼ������ͨ��������
void DFS(int u, int depth) {
  vis[u] = true; // ���Ϊ�ѷ��ʡ�
  // ö��u���ھӣ�����u�������Դﵽ�Ľڵ㡣
  // �ڵ��Ŵ�0--N-1.

  // �Խڵ���в�����

  // ö����һ���ڵ㡣
  for (int v = 0; v < N; ++v) {
    if (!vis[v] && G[u][v] != INF) {
      // u�ɴ����δ���ʡ�
      DFS(v, depth + 1);
    }
  }
  // ע�⣬�ͻ��ݷ���DFS��ͬ�����ﲻ��Ҫ�ָ�vis��ֵ����Ϊ���ǲ���
  // ��ö��ȫ����·����������Ҷ�ӵ�·���������Ƿ���ȫ���ڵ㡣
  // �����ö��ȫ��·������һ���ڵ�ᱻ���ʶ�Σ���Ϊһ���ڵ���Գ���
  // �ڶ��·����������Ƿ���ȫ���ڵ㣬��һ���ڵ�ֻӦ�ñ�����һ�Ρ�

  // ����ע�⣬���ݷ�����ʱ��������һ���������޻�����νṹ���и�����
  // ��DFS����ͼʱ��������ͼ�������л��ġ����Ի��ݷ�����Ҫvis���� ����Ϊ�޻�����
  // ��DFS����ͼ��Ҫ��
}

// ��������ͼ�����ܰ��������ͨ�飩��
void DFSTrave() {
  // �ȳ�ʼ����һ�α�����vis����ȫ��Ϊtrue��
  fill(vis, vis + N, false);
  for (int v = 0; v < N; ++v) {
    if (!vis[v]) {
      // һ���µ���ͨ������
      DFS(v, 1);
    }
  }
}

/*
�ڽӱ��DFS��
*/

vector<int> Adj[MAXN];

/*
�� �ڽӾ��� �İ汾������һ�£�����ö��u�Ŀɴ�ڵ�Ĳ��֡�
*/
void DFS2(int u, int depth) {
  vis[u] = true;
  for (int i = 0; i < Adj[u].size(); ++i) {
    // ����u���ڽӱ�
    int v = Adj[u][i];
    if (!vis[v]) {
      DFS2(v, depth + 1);
    }
  }
}

void DFSTrave2() {
  // ��DFSTrave��һ���ģ����˵���DFS2.
  for (int v = 0; v < N; ++v) {
    if (!vis[v]) {
      DFS2(v, 1); // ��ʼ���Ϊ1.
    }
  }
}

/*
BFS ģ��
BFS��Ҫһ��inq���飬������DFS��vis�������ƣ���־һ���ڵ��Ƿ��������С�
1. ÿ���ڵ�����һ�Σ�������һ�Ρ�
2. һ���ڵ����inq=falseʱ������С�
3. һ���ڵ������к�Ӧ��������inq=true��
4. һ��BFS���ã��ܰ�u���ڵ���ͨ������нڵ��inq��Ϊtrue�����ͼ������ͨͼ��
��Ҫ������inq=false�Ľڵ������һ��BFS��ÿ�ζ�����һ����ͨ�顣
*/

bool inq[MAXN];

void BFS(int u) {
  queue<int> Q;
  Q.push(u);
  inq[u] = true;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (int v = 0; v < N; ++v) {
      if (!inq[v] && G[u][v] != INF) {
        // v��u���ھӣ�����vδ����ӡ�
        Q.push(v);
        inq[v] = true;
      }
    }
  }
}

// ȫͼBFS��
void BFSTrave() {
  fill(inq, inq + N, false); // ���ȫ���ڵ�δ��ӡ�
  for (int u = 0; u < N; ++u) {
    if (!inq[u]) { // �����DFSTrave�����Ƶġ�
      BFS(u);
    }
  }
}

// �ڽӱ��BFS��ȫ���ƣ������ظ���

/*
����Դ��s����BFS�����и��ڵ�Ĳ�š�
*/
struct Node {
  int v;     // �ڵ㡣
  int layer; // ���
};

/*
Node �������������Ĳ�š�
������Ҫ��������
*/
vector<Node> Adj2[MAXN];

void BFS2(int s) { // BFS���ĸ�����Դ�㡣
  queue<Node> Q;
  // Դ������Ϊ0��Դ����ӡ�
  Node start;
  start.v = s;
  start.layer = 0;
  Q.push(start);
  inq[start.v] = true;
  while (!Q.empty()) {
    Node topNode = Q.front();
    Q.pop();
    int u = topNode.v;
    for (int i = 0; i < Adj2[u].size(); ++i) {
      Node next = Adj2[u][i];
      next.layer = topNode.layer +
                   1; // ע�⣬next����inq=true������û��ϵ����Ϊ��������ˡ�
      if (!inq[next.v]) {
        // �ó���next�Ĳ�š�
        inq[next.v] = true;
        Q.push(next);
      }
    }
  }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) { return 0; }
