#include <stdio.h>
#include <stdlib.h>

/*
普通树的几种表示方法，
以及树的基本属性的获取。

表示方法：
1. 孩子-兄弟表示法，每个节点保留第一个孩子和下一个兄弟的指针。
2. 孩子表示法，每个节点保留所有孩子的指针。
3. 静态数组，将第1中表示法用静态链表表示。

基本属性：
1. 树的节点总数N。
        N=0，则为空树。遍历所有节点即可获取，或者维护size变量。

2. 节点的度，等于节点的孩子数。

3. 树的度，即所有节点的度的最大值。

4. 节点的层次，根节点在第一层，其他节点的层次是其父节点层次加1.
5. 树的深度，树的所有节点的最大层次。
6. 树的边的总数等于节点总数减1.
*/

typedef struct Node Node;
struct Node {
  int data;
  Node *child; // 第一个孩子
  Node *sibl;  // 下一个兄弟。
};

// 节点的度就是孩子数。
int NodeDegree(Node *n) {
  int sum = 0;
  Node *ch;
  for (ch = n->child; ch; ch = ch->sibl) {
    ++sum;
  }
  return sum;
}

int NodeCount(Node *n) {
  int sum = 0;
  Node *ch;

  if (!n)
    return 0;
  for (ch = n->child; ch; ch = ch->sibl) {
    sum += NodeCount(ch);
  }
  return sum + 1;
}

int EdgeCount(Node *n) { return NodeCount(n) - 1; }

/*
判断一棵树是否为空。
*/
int IsEmpty(Node *n) { return 0 == NodeCount(n); }
