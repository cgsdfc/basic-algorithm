/*
用静态数组表示二叉树
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int data;
  // 下面三个域都是数组下标，为-1时，表示NULL。
  int left, right;
  int parent;
} Node;

#define MAXN 100

// typedef Node Tree[MAXN];

/*
 从输入中建树。输入格式为：N N行，
 每行为 i left right，三个整数。表示i号节点的左节点号码是left，右节点是right。
 data与i相同。
 注意，树的节点数是N，除非要按输入顺序遍历所有节点，
 否则保留根节点即可访问整棵树。并且假设合法节点的编号都是连续的
 从0到N-1，那么从0到N-1就没有非法数据，并且用根节点也访问不了非法数据。
 */

int ReadTree(Node t[]) {
  int N;
  int i;
  int root;

  scanf("%d", &N);
  // 把所有指针域置为-1.
  for (i = 0; i < N; ++i) {
    t[i].left = t[i].right = t[i].parent = -1;
  }
  for (i = 0; i < N; ++i) {
    // 如果left或right为NULL，则假设输入数据就是-1，不用特殊处理。
    int x, left, right;
    scanf("%d%d%d", &x, &left, &right);
    t[x].left = left;
    t[x].right = right;
    t[x].data = x;

    // 设置父节点。
    if (left != -1) {
      t[left].parent = x;
    }
    if (right != -1) {
      t[right].parent = x;
    }
  }

  //	for (i=0;i<N;++i) {
  //		printf("%d %d %d %d\n", t[i].data, t[i].left, t[i].right,
  //t[i].parent);
  //	}

  // 没有父节点的节点，就是根节点。
  root = -1;
  for (i = 0; i < N; ++i) {
    if (t[i].parent == -1) {
      root = i;
      break;
    }
  }
  assert(root != -1);
  return root;
}

void PreOrderTraversal(Node t[], int root) {
  if (root != -1) {
    printf("%d ", t[root].data);
    PreOrderTraversal(t, t[root].left);
    PreOrderTraversal(t, t[root].right);
  }
}

void TestStaticBinTree(void) {
  int root;
  Node t[MAXN];

  root = ReadTree(t);
  PreOrderTraversal(t, root);
}
