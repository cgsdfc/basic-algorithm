#include <algorithm>
#include <cassert>
#include <cstdio>
#include <queue>
using namespace std;
/*
用《完全二叉查找树》的思路，
先建树，然后计算各子树的大小，
然后对键值数组排序得出中序，
然后中序建树。最后层序输出。
复杂度为nlogn，由于n较小，所以不会超时。

思路二：
1. 建树，然后中序遍历得出标号的中序。
2. 对键值数组排序，得出填入后的中序。
3. 由于标号和键值一一对应，立刻知道某键值对应的标号，
将其填入。
4. 层序输出。
*/

#define MAXN 105
struct Node {
  int data;
  int lchild, rchild;
} node[MAXN];

int N;
int data[MAXN]; // 键值。

// 标号的中序序列。
struct {
  int data[MAXN];
  int len;
} in;

void Inorder(int root) {
  if (root != -1) {
    Inorder(node[root].lchild);
    in.data[in.len++] = root;
    Inorder(node[root].rchild);
  }
}

const int Root = 0;

void BFS(int &i) {
  queue<int> Q;
  Q.push(Root);
  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();
    printf("%d%s", node[now].data, i == N - 1 ? "\n" : " ");
    i++;
    if (node[now].lchild != -1) {
      Q.push(node[now].lchild);
    }
    if (node[now].rchild != -1) {
      Q.push(node[now].rchild);
    }
  }
}

void Fill() {
  assert(N == in.len);
  // 把data填入node
  for (int i = 0; i < N; ++i) {
    node[in.data[i]].data = data[i];
  }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    // 输入的格式和表示的格式完全相同。
    scanf("%d%d", &node[i].lchild, &node[i].rchild);
  }
  // 输入关键字。
  for (int i = 0; i < N; ++i) {
    scanf("%d", &data[i]);
  }
  // 排序得中序
  sort(data, data + N);
  // 下标的中序。
  Inorder(Root);
  Fill();
  int i = 0;
  BFS(i);

  return 0;
}
