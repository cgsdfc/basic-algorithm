#include <cassert>
#include <climits>
#include <cstdio>
#include <queue>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 总叶子节点数。
#define MAXN 105
// 哈夫曼树的总节点数，由总叶子节点数确定。
#define MAXV (2 * MAXN - 1)

struct Node {
  int parent;
  // 因为是自底向上建树，所以不需要child，
  // 记录当前节点是左孩子还是右孩子即可。
  bool isRight; // 是右孩子，对根节点无意义。
                //	bool isLeaf; // 是叶子节点。
  int weight;   // 权重。
  /*
  题目给的算法，没有用堆，所以当遇到相同的权重时，
  它优先选择输入序列里面考前的元素（也就是用线性扫描来
  找最小值），我们用堆模拟，必须还原这种优先级，才能
  得到一样的答案。
  */
  int id;
} node[MAXV];

int index = 0;

int NewNode() { return index++; }

struct cmp {
  // 注意：相同的权重，id小的先出现，因为要模拟线性扫描的特性。
  bool operator()(int a, int b) {
    // weight 小的先出队。
    if (node[a].weight != node[b].weight) {
      return node[a].weight > node[b].weight;
    }
    // id小的先出队。
    return node[a].id > node[b].id;
  }
};

// 构建哈夫曼树，返回根节点。
int Build(int N) {
  // 注意哈夫曼编码必备小顶堆，即greater。
  priority_queue<int, vector<int>, cmp> Q;
  // 输入N个权重，构建成叶子节点。
  int id = 0;
  while (N--) {
    int w;
    scanf("%d", &w);
    int p = NewNode();
    //		node[p].isLeaf=true;
    node[p].weight = w;
    node[p].parent = -1; // 一开始既是根节点，也是叶节点。
    node[p].id = id++;
    Q.push(p);
  }
  // 新生成的节点，其id要继续编号。
  while (Q.size() > 1) {
    int a = Q.top();
    Q.pop();
    int b = Q.top();
    Q.pop();
    /*
    注意，两个最小元，以id的顺序出现。
    */
    if (node[a].id > node[b].id) {
      swap(a, b);
    }

    //		printf("%d %d\n", node[a].weight, node[b].weight);

    // 这里固定，先出队的是左孩子。
    node[a].isRight = false;
    node[b].isRight = true;
    // 合并为根。
    int root = NewNode();
    node[root].weight = node[a].weight + node[b].weight;
    node[root].parent = -1; // 不知道。
    //		node[root].isLeaf=false; // 我有孩子，不是叶子。
    node[root].id = id++;
    node[a].parent = node[b].parent = root;
    Q.push(root);
  }
  return Q.top();
}

// 对叶子找根，生成编码。
void FindCode(int v, int root) {
  //	assert(node[v].isLeaf);
  vector<int> code;
  while (v != root) {
    //		printf("%d ", node[v].weight);
    code.push_back((int)node[v].isRight);
    v = node[v].parent;
  }
  for (int i = code.size() - 1; i >= 0; --i) {
    printf("%d", code[i]);
  }
  printf("\n");
}

/*
生成哈夫曼编码。
注意：
1. 靠近根的节点权重大，靠近叶子的节点权重小，因此，
要用小顶堆，每次选择权重最小的两个节点进行合并。
*/
int main(int argc, char **argv) {
  int N;
  while (scanf("%d", &N) != EOF) {
    index = 0;
    int root = Build(N);
    // 注意，0--N-1是叶子。
    for (int i = 0; i < N; ++i) {
      FindCode(i, root);
    }
  }
  return 0;
}
