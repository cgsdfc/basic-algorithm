#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 105

char pre[MAXN];
int N;

struct Node {
  char data;
  Node *lchild;
  Node *rchild;
};

/*
本题的关键在于如何划分子树的前序序列。
1. 根是第一个元素，如果根是#，则区间长度应该是1，则为NULL。
2. 找到第一个#，位置i，必定存在。
3. 找到第一个#后面的第一个非#，位置j，如果找到则左子树为：
preL+1, j-1

左子树和右子树必定由一段连续的#分割，即我们要找到第一段连续的#，
以此来分割左右子树，注意左右子树可能为空。
*/
// 这个算法是错误的。
// Node* Create(int preL, int preR) {
//	for (int i=preL;i<=preR;++i) {
//		putchar(pre[i]);
//	}
//	puts("");
//
//	if (preL == preR) {
//		assert(pre[preL] == '#');
//		return NULL;
//	}
//
//	assert(pre[preL] != '#');
//	Node* root=new Node;
//	root->data=pre[preL];
//
//	int i,j; // 找到第一段连续的#。
//	for (i=preL;pre[i]!='#'&&i<=preR;++i);
//	assert(i <= preR); // 必须至少有一个#。
//	for (j=i;pre[j]=='#'&&j<=preR;++j);
//	if (j>preR) { // 注意这个条件，如果后面的全是#，那么j会超过preR。
//		// 右子树为空，给他留下一个#
//		j--;
//	}
////	printf("i %d j %d\n", i, j);
//
//	// j就是左右子树的分界线。
//	root->lchild=Create(preL+1, j-1);
//	root->rchild=Create(j, preR);
//	return root;
//}

/*
注意到，一颗二叉树，#的数量记为E，节点的数量记为N，则有关系
E = N + 1 成立，利用这个关系把中序序列分割为左右子树，使得左右
序列都满足此关系。
*/

Node *Create(int preL, int preR) {
  if (preL == preR) {
    // 空树必为 #
    return NULL;
  }
  Node *root = new Node;
  root->data = pre[preL];
  int numN = 0; // 节点数。
  int numE = 0; // #数。
  /*
  如果整体满足 N+1=E,并且左子树满足NL+1=EL，
  可以证明，右子树必定满足NR+1=ER，
  因为 NL+NR+1=N, EL+ER=E.
  */
  int i;
  for (i = preL + 1; i <= preR; ++i) {
    if (numN + 1 == numE) {
      break;
    }
    if (pre[i] == '#') {
      ++numE;
    } else {
      ++numN;
    }
  }
  root->lchild = Create(preL + 1, i - 1);
  root->rchild = Create(i, preR);
  return root;
}

void Inorder(Node *root) {
  if (root) {
    Inorder(root->lchild);
    printf("%c ", root->data);
    Inorder(root->rchild);
  }
}

int main(int argc, char **argv) {
  while (scanf("%s", pre) != EOF) {
    N = strlen(pre);
    Node *root = Create(0, N - 1);
    Inorder(root);
    puts("");
  }
  return 0;
}
