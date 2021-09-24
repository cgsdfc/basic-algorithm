#include <cstdio>

using namespace std;

/*
层序中序建树

核心思想：
1. 层序的第一个元素是当前的根R；
2. 在中序中，根据R划分左子树和右子树的中序；
3. 根据左子树和右子树的中序，把层序划分为左子树的层序和右子树的层序。
注意层序的特点：保持在原序列中的顺序，单独把属于一棵子树的元素提出来，
就得到了这棵子树的层序。
*/

struct Node {
  int data;
  Node *lchild;
  Node *rchild;

  Node(int v) {
    data = v;
    lchild = rchild = NULL;
  }
};

#define MAXN 100

int in[MAXN];    // 中序序列。
int layer[MAXN]; // 层序序列。

// 直接写构造函数。
// Node* newNode(int v) {
//	Node* p=new Node;
//	p->data=v;
//	p->lchild=p->rchild=NULL;
//	return p;
//}

Node *Create(int inL, int inR, int layer[], int len) {
  // 层序为空，则空树。
  if (len <= 0) {
    return NULL;
  }

  int v = layer[0];
  Node *root = new Node(v);
  int k;
  for (int i = inL; i <= inR; ++i) {
    if (in[i] == v) {
      k = i;
      break;
    }
  }

  // 左右子树的中序序列。
  int layerL[MAXN], lenL = 0;
  int layerR[MAXN], lenR = 0;
  for (int i = 1; i < len; ++i) {
    int x = layer[i];
    bool isL = false;
    // 如果x出现在左子树的中序，则x属于左子树，否则就是右子树。
    for (int j = inL; j < k; ++j) {
      if (in[j] == x) {
        isL = true;
        break;
      }
    }
    if (isL) {
      layerL[lenL++] = x;
    } else {
      layerR[lenR++] = x;
    }
  }
  root->lchild = Create(inL, k - 1, layerL, lenL);
  root->rchild = Create(k + 1, inR, layerR, lenR);
  return root;
}
