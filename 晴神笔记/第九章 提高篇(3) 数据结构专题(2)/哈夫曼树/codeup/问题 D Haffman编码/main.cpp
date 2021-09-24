#include <cstdio>
#include <queue>
#include <string>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int N;

struct Node {
  char ch;
  int weight;
  string code; // ���ڵ�ա�
  int lchild, rchild;
};

// ��Ŀû�и����ڵ������Ͻ硣
vector<Node> node;

struct cmp {
  bool operator()(int a, int b) {
    if (node[a].weight != node[b].weight) {
      return node[a].weight > node[b].weight;
    }
    // ch С���ȳ��ӡ�
    return node[a].ch > node[b].ch;
  }
};

int Build(int N) {
  priority_queue<int, vector<int>, cmp> Q;

  for (int i = 0; i < N; ++i) {
    getchar();
    scanf("%c %d", &node[i].ch, &node[i].weight);
    node[i].lchild = node[i].rchild = -1;
    Q.push(i);
  }
  int index = N; // ��Ҷ�ڵ���䡣
  while (Q.size() > 1) {
    int a = Q.top();
    Q.pop();
    int b = Q.top();
    Q.pop();
    // �ȳ��ӵ������ӡ�
    int root = index++;
    node[root].lchild = a;
    node[root].rchild = b;
    node[root].weight = node[a].weight + node[b].weight;
    node[root].ch = node[a].ch;
    Q.push(root);
  }
  return Q.top();
}

// ���ɱ��룬����node[0--N-1]���ǰ�������˳��ģ�����ֱ�������
void DFS(int root) {
  // �߽�������Ҷ�ڵ㡣
  if (node[root].lchild == -1) {
    return;
  }
  int lchild = node[root].lchild;
  int rchild = node[root].rchild;

  node[lchild].code = node[rchild].code = node[root].code;
  node[lchild].code.push_back('0');
  node[rchild].code.push_back('1');
  DFS(lchild);
  DFS(rchild);
}

int main(int argc, char **argv) {
  while (scanf("%d", &N) != EOF) {
    node.resize(2 * N + 5);
    int root = Build(N);
    DFS(root);
    for (int i = 0; i < N; ++i) {
      printf("%c:%s\n", node[i].ch, node[i].code.c_str());
    }
  }
  return 0;
}
