/*
给定一个序列，按此顺序将元素插入到二叉搜索树中，
则一个序列唯一确定一个二叉搜索树。但是一个二叉搜索树可以对应多个序列，
如：
3 1 2
3 2 1
对应的都是
3
1 2

输入：
现在给定若干个序列，判断第一个序列所对应的二叉树是否和其他序列所对应的二叉树相同。
第一行是两个整数N，M，表示接下来有N行，每行有M个整数，表示一个序列。

输出：
N-1行，每一行输出Yes，如果对应的序列和第一个序列具有相同的二叉树，否则输出No。
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// 最大序列长度
#define MAXM 100

/*
思路有：
1. 对第一个序列，建树，然后对其他每个序列建树，利用递归判断两个树是否相同。
2. 只对第一个序列建树，然后对其他每个序列，按序查找元素，并在树上做标记，
表示一个元素被查找过了。一个序列如果和一个树相同，则每一个元素在查找过程中，
所经过的节点都是被查找过的，并且本元素未被查找过。如果不符合这个要求，则序列和
树不相同。

需要以下函数：
1. 读数建树 BuildTree。
2. 查找判断序列是否等于树 Judge。
*/

typedef struct BinNode BinNode;
struct BinNode {
  int v;
  int flag;
  BinNode *left, *right;
};

static BinNode *Insert(BinNode *t, int x) {
  if (!t) {
    // 插入到一颗空树，则新元素成为根。
    t = malloc(sizeof(BinNode));
    t->v = x;
    t->left = t->right = NULL;
    t->flag = 0;
    return t;
  }
  if (x > t->v) {
    // 插入右子树。
    t->right = Insert(t->right, x);
  } else if (x < t->v) {
    // 插入左子树。
    t->left = Insert(t->left, x);
  } else {
    // 在元素无重复的前提下，x已经存在，不插入。
  }
  return t;
}

// n是序列长度，读入n个数，依次插入二叉树。
static BinNode *BuildTree(int n) {
  BinNode *tr = NULL;
  int i;
  for (i = 0; i < n; ++i) {
    int v;
    scanf("%d", &v);
    tr = Insert(tr, v);
  }
  return tr;
}

// 检查x是否可插入。
static int Check(BinNode *tr, int x) {
  while (tr) {
    if (x != tr->v) {
      // 沿途节点。
      if (!tr->flag)
        return 0;
      tr = x > tr->v ? tr->right : tr->left;
    } else {
      if (tr->flag) {
        // 已经有此元素
        return 0;
      }
      tr->flag = 1;
      return 1;
    }
  }
  // 查无此人。
  return 0;
}

int a[MAXM];

// 读入n个数，判断序列与树是否等价。
static int Judge(BinNode *tr, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (i = 0; i < n; ++i) {
    if (!Check(tr, a[i])) {
      return 0;
    }
  }
  return 1;
}

// 把flag全部设为0.
static void Reset(BinNode *tr) {
  if (tr) {
    tr->flag = 0;
    Reset(tr->left);
    Reset(tr->right);
  }
}

void SeqSameTreeMain(void) {
  int N, M;
  BinNode *tr;
  int i;

  scanf("%d%d", &N, &M);
  // 对第一个序列建树。
  tr = BuildTree(M);
  for (i = 1; i < N; ++i) {
    int res = Judge(tr, M);
    puts(res ? "Yes" : "No");
    Reset(tr);
  }
}
