#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1005
int N; // �ڵ�����
int L; // �����Ĳ������ơ�

// ��BFSʱҪ��¼��ţ��Ա����Ʋ�������������ֵ��
struct Node {
  int v;
  int layer;
  Node(int _v, int _layer) : v(_v), layer(_layer) {}
};

vector<int> Adj[MAXN]; // �ڽӱ�
bool inq[MAXN];        // BFS�ر���

/*
����Ҫ���Դ��s���������Ʋ���������L��BFS���������ĵ�����������s������
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
      // ע�⣬�����������
      // p�Ĳ��û�г���L������L=1��p��s���ھӣ���ôpû�г���L��
      // ����pû����ӡ�
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
  // ����ÿ���û����ڽӱ�
  // ע�⣬����������ģ�Ҫ����
  for (int i = 1; i <= N; ++i) {
    int k;
    scanf("%d", &k); // ��ע��������
    while (k--) {
      int x;
      scanf("%d", &x);
      // i ��ע x��x ��i��ע��ת����Ϣ��x��i��
      Adj[x].push_back(i);
    }
  }
  int K;
  scanf("%d", &K);
  while (K--) {
    int s; // Դ�㡣
    scanf("%d", &s);
    fill(inq, inq + N + 1, false);
    int ans = BFS(s);
    printf("%d\n", ans);
  }

  return 0;
}
