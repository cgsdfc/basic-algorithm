/*
�þ�̬�����ʾ������
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int data;
  // �����������������±꣬Ϊ-1ʱ����ʾNULL��
  int left, right;
  int parent;
} Node;

#define MAXN 100

// typedef Node Tree[MAXN];

/*
 �������н����������ʽΪ��N N�У�
 ÿ��Ϊ i left right��������������ʾi�Žڵ����ڵ������left���ҽڵ���right��
 data��i��ͬ��
 ע�⣬���Ľڵ�����N������Ҫ������˳��������нڵ㣬
 ���������ڵ㼴�ɷ��������������Ҽ���Ϸ��ڵ�ı�Ŷ���������
 ��0��N-1����ô��0��N-1��û�зǷ����ݣ������ø��ڵ�Ҳ���ʲ��˷Ƿ����ݡ�
 */

int ReadTree(Node t[]) {
  int N;
  int i;
  int root;

  scanf("%d", &N);
  // ������ָ������Ϊ-1.
  for (i = 0; i < N; ++i) {
    t[i].left = t[i].right = t[i].parent = -1;
  }
  for (i = 0; i < N; ++i) {
    // ���left��rightΪNULL��������������ݾ���-1���������⴦��
    int x, left, right;
    scanf("%d%d%d", &x, &left, &right);
    t[x].left = left;
    t[x].right = right;
    t[x].data = x;

    // ���ø��ڵ㡣
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

  // û�и��ڵ�Ľڵ㣬���Ǹ��ڵ㡣
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
