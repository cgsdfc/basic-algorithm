#include <cassert>
#include <cstdio>
#include <queue>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 15

struct Node {
  //	int data; // 号序。
  int lchild;
  int rchild;
};

/*
本题的输入格式用静态链表比较方便。
*/
Node node[MAXN];

bool has[MAXN]; // 某号节点是否有父亲。

int N; // 节点数。

void Invert(int root) {
  if (root != -1) {
    swap(node[root].lchild, node[root].rchild);
    Invert(node[root].lchild);
    Invert(node[root].rchild);
  }
}

int Create(int N) {
  for (int i = 0; i < N; ++i) {
    node[i].lchild = node[i].rchild = -1;
  }

  for (int i = 0; i < N; ++i) {
    char a[5], b[5];
    scanf("%s%s", a, b);
    //		node[i].data=i;
    if (a[0] != '-') {
      node[i].lchild = a[0] - '0';
      has[node[i].lchild] = true;
    }
    if (b[0] != '-') {
      node[i].rchild = b[0] - '0';
      has[node[i].rchild] = true;
    }
  }
  for (int i = 0; i < N; ++i) {
    if (!has[i]) {
      return i;
    }
  }
  return -1;
}

void BFS(int root) {
  queue<int> Q;
  Q.push(root);
  int i = 0;

  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();
    printf("%d%s", now, i == N - 1 ? "\n" : " ");
    ++i;
    if (node[now].lchild != -1) {
      Q.push(node[now].lchild);
    }
    if (node[now].rchild != -1) {
      Q.push(node[now].rchild);
    }
  }
}

int i; // 打印元素。
void Inorder(int root) {
  if (root != -1) {
    Inorder(node[root].lchild);
    printf("%d%s", root, i == N - 1 ? "\n" : " ");
    ++i;
    Inorder(node[root].rchild);
  }
}

int main(int argc, char **argv) {
  scanf("%d", &N);
  int root = Create(N);
  assert(root != -1);
  Invert(root);
  BFS(root);
  Inorder(root);

  return 0;
}
