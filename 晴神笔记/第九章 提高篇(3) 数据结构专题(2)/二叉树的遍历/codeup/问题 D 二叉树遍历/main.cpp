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
����Ĺؼ�������λ���������ǰ�����С�
1. ���ǵ�һ��Ԫ�أ��������#�������䳤��Ӧ����1����ΪNULL��
2. �ҵ���һ��#��λ��i���ض����ڡ�
3. �ҵ���һ��#����ĵ�һ����#��λ��j������ҵ���������Ϊ��
preL+1, j-1

���������������ض���һ��������#�ָ������Ҫ�ҵ���һ��������#��
�Դ����ָ�����������ע��������������Ϊ�ա�
*/
// ����㷨�Ǵ���ġ�
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
//	int i,j; // �ҵ���һ��������#��
//	for (i=preL;pre[i]!='#'&&i<=preR;++i);
//	assert(i <= preR); // ����������һ��#��
//	for (j=i;pre[j]=='#'&&j<=preR;++j);
//	if (j>preR) { // ע�������������������ȫ��#����ôj�ᳬ��preR��
//		// ������Ϊ�գ���������һ��#
//		j--;
//	}
////	printf("i %d j %d\n", i, j);
//
//	// j�������������ķֽ��ߡ�
//	root->lchild=Create(preL+1, j-1);
//	root->rchild=Create(j, preR);
//	return root;
//}

/*
ע�⵽��һ�Ŷ�������#��������ΪE���ڵ��������ΪN�����й�ϵ
E = N + 1 ���������������ϵ���������зָ�Ϊ����������ʹ������
���ж�����˹�ϵ��
*/

Node *Create(int preL, int preR) {
  if (preL == preR) {
    // ������Ϊ #
    return NULL;
  }
  Node *root = new Node;
  root->data = pre[preL];
  int numN = 0; // �ڵ�����
  int numE = 0; // #����
  /*
  ����������� N+1=E,��������������NL+1=EL��
  ����֤�����������ض�����NR+1=ER��
  ��Ϊ NL+NR+1=N, EL+ER=E.
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
