#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
二叉查找树（BST）的操作的实现。
1. 查找给定元素。
2. 查找最大值，最小值。
3. 插入元素（是建树的基本操作）。
4. 删除元素。
*/

typedef struct BinNode BinNode;
struct BinNode {
  int v;
  BinNode *left, *right;
};

/*
在以t为根的树中查找x，找到则返回保存x的节点，否则返回NULL。
*/
BinNode *Find(BinNode *t, int x) {
  if (!t)
    return NULL; // 空树必定查找失败。
  /*
  以t->v为路标，当x小于它时，往左边继续找，当x大于ta时，往右边继续找。
  */
  if (x < t->v) {
    return Find(t->left, x);
  } else if (x > t->v) {
    return Find(t->right, x);
  } else {
    // 要找的x正好在根。
    return t;
  }
}

/*
迭代版的Find，和二分查找类似，比较容易实现，并且更加高效。
*/
BinNode *IterFind(BinNode *t, int x) {
  while (t) {
    if (x < t->v) {
      t = t->left;
    } else if (x > t->v) {
      t = t->right;
    } else {
      return t;
    }
  }
  return NULL;
}

/*
返回最小元素对应的节点，空树返回NULL。
*/
BinNode *FindMin(BinNode *t) {
  if (!t)
    return NULL;
  while (t->left) {
    t = t->left;
  }
  return t;
}

/*
返回最大元素对应的节点，空树返回NULL。
*/
BinNode *FindMax(BinNode *t) {
  if (!t)
    return NULL;
  while (t->right) {
    t = t->right;
  }
  return t;
}

/*
递归实现FindMax。其实Find和FindMax都是尾递归，容易用迭代实现。
*/
BinNode *RecurFindMax(BinNode *t) {
  if (t) {
    if (!t->right)
      return t;
    return RecurFindMax(t->right);
  }
  return NULL;
}

/*
插入操作，t是被插入的树的根，x是新元素。返回插入后的新树的根。
不考虑平衡操作，则新插入的节点总是成为叶节点。
*/
BinNode *Insert(BinNode *t, int x) {
  if (!t) {
    // 插入到一颗空树，则新元素成为根。
    t = malloc(sizeof(BinNode));
    t->v = x;
    t->left = t->right = NULL;
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

/*
在以t为根的树中删除x对应的元素，返回删除后的树的根。
*/
BinNode *Delete(BinNode *t, int x) {
  if (!t) {
    // 空树无法删除任何元素。
    // 出现空树说明元素找不到。
    printf("NotFound\n");
    return NULL;
  }
  // 先递归找到要删除的节点位置。
  if (x < t->v) {
    // 要删的元素在左子树。删完后，t仍是树根。
    t->left = Delete(t->left, x);
  } else if (x > t->v) {
    t->right = Delete(t->right, x);
  } else {
    // 找到了x对应的节点。
    /*
    分为三种情况：
    1. t是叶子节点，则直接free掉，把NULL返回个上层。
    2. t只有一个孩子，则把t的唯一孩子挂到t的父节点，删掉t。
    3. t有两个孩子，则从左子树找到最大值（或者右子树的最小值）m，
            用m代替t的值，然后把m对应的节点删掉。因为m是最大值（最小值）节点，
            必定可以归为1，2情况。
    */

    // 情况3
    if (t->left && t->right) {
      // 找左子树的最大值，或者右子树的最小值。
      BinNode *tmp = FindMax(t->left);
      assert(tmp);
      // 以最大值代替t的值。
      t->v = tmp->v;
      // 从左子树中删除tmp
      t->left = Delete(t->left, tmp->v);
    } else {
      // t是一定要free的，在此之前，先保存它的非空的孩子（或者NULL）。
      BinNode *tmp = t;
      if (t->left) {
        t = t->left;
      }
      if (t->right) {
        t = t->right;
      }
      free(tmp);
    }
  }
  return t;
}

/*
常见操作，从一个数组中，按顺序插入元素建成一个树。
*/
BinNode *BuildTree(int a[], int n) {
  int i;
  BinNode *t = NULL; // 初始是一个空树，必须初始化。

  for (i = 0; i < n; ++i) {
    t = Insert(t, a[i]);
  }
  return t;
}

/*
以递归方式释放树t的内存。
注意，采用后序遍历。
*/
void FreeTree(BinNode *t) {
  if (t) {
    FreeTree(t->left);
    FreeTree(t->right);
    free(t);
  }
}

/*
因括号表达式打印二叉树，
比如 (a (b) (c)) 。
*/
void PrintTree(BinNode *t) {
  if (t) {
    putchar('(');
    printf("%d ", t->v);
    PrintTree(t->left);
    putchar(' ');
    PrintTree(t->right);
    putchar(')');
  } else {
    printf("nil");
  }
}

void TestBST(void) {
  int a[] = {42, 112, 431, 16, 632};
  BinNode *t = BuildTree(a, sizeof(a) / sizeof(a[0]));
  PrintTree(t);
}

int main(int argc, char *argv[]) {
  TestBST();
  return 0;
}
