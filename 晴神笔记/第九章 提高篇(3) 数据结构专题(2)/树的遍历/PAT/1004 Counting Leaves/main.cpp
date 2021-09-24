#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
按层序输出每一层的叶节点数量。
还是BFS，一个节点出队时，如果是叶节点，则该层的叶节点数加一。
BFS还是要计算深度，即层。
*/
#define MAXN 105

struct Node {
  int deep;
  vector<int> child;
} node[MAXN];

int level[MAXN]; // 每层的叶节点数。
int MaxLevel;    // 最大层数。注意层从1开始。
const int root = 1;
int N, M; // 总节点，非叶节点。

int BFS() {
  queue<int> Q;
  Q.push(root);
  node[root].deep = 1;
  int ans = 0;

  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();

    if (node[now].child.empty()) {
      // 发现一个叶节点。
      level[node[now].deep]++;
    }
    if (node[now].deep > ans) {
      ans = node[now].deep;
      // 注意，如果要对每个节点做一个操作，
      // 必须在出队这里做，因为下面的入队操作不对所有节点执行（根不执行）。
    }
    for (int i = 0; i < node[now].child.size(); ++i) {
      int p = node[now].child[i];
      Q.push(p);
      node[p].deep = node[now].deep + 1;
    }
  }
  return ans;
}

int main(int argc, char **argv) {
  scanf("%d%d", &N, &M);
  if (!N)
    return 0;
  for (int i = 0; i < M; ++i) {
    // 输入非叶节点行。
    int id, K;
    scanf("%d%d", &id, &K);
    while (K--) {
      int c;
      scanf("%d", &c);
      node[id].child.push_back(c);
    }
  }
  //	puts("input");

  MaxLevel = BFS();
  // 输出每层的叶节点数。
  for (int i = 1; i <= MaxLevel; ++i) {
    printf("%d%s", level[i], i == MaxLevel ? "\n" : " ");
  }
  return 0;
}
