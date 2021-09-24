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
  string code; // 根节点空。
  int lchild, rchild;
};

// 题目没有给出节点数量上界。
vector<Node> node;

struct cmp {
  bool operator()(int a, int b) {
    if (node[a].weight != node[b].weight) {
      return node[a].weight > node[b].weight;
    }
    // ch 小的先出队。
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
  int index = N; // 非叶节点分配。
  while (Q.size() > 1) {
    int a = Q.top();
    Q.pop();
    int b = Q.top();
    Q.pop();
    // 先出队的是左孩子。
    int root = index++;
    node[root].lchild = a;
    node[root].rchild = b;
    node[root].weight = node[a].weight + node[b].weight;
    node[root].ch = node[a].ch;
    Q.push(root);
  }
  return Q.top();
}

// 生成编码，由于node[0--N-1]就是按照输入顺序的，可以直接输出。
void DFS(int root) {
  // 边界条件是叶节点。
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
