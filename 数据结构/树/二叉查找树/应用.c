/*
����һ�����У�����˳��Ԫ�ز��뵽�����������У�
��һ������Ψһȷ��һ������������������һ���������������Զ�Ӧ������У�
�磺
3 1 2
3 2 1
��Ӧ�Ķ���
3
1 2

���룺
���ڸ������ɸ����У��жϵ�һ����������Ӧ�Ķ������Ƿ��������������Ӧ�Ķ�������ͬ��
��һ������������N��M����ʾ��������N�У�ÿ����M����������ʾһ�����С�

�����
N-1�У�ÿһ�����Yes�������Ӧ�����к͵�һ�����о�����ͬ�Ķ��������������No��
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// ������г���
#define MAXM 100

/*
˼·�У�
1. �Ե�һ�����У�������Ȼ�������ÿ�����н��������õݹ��ж��������Ƿ���ͬ��
2. ֻ�Ե�һ�����н�����Ȼ�������ÿ�����У��������Ԫ�أ�������������ǣ�
��ʾһ��Ԫ�ر����ҹ��ˡ�һ�����������һ������ͬ����ÿһ��Ԫ���ڲ��ҹ����У�
�������Ľڵ㶼�Ǳ����ҹ��ģ����ұ�Ԫ��δ�����ҹ���������������Ҫ�������к�
������ͬ��

��Ҫ���º�����
1. �������� BuildTree��
2. �����ж������Ƿ������ Judge��
*/

typedef struct BinNode BinNode;
struct BinNode {
  int v;
  int flag;
  BinNode *left, *right;
};

static BinNode *Insert(BinNode *t, int x) {
  if (!t) {
    // ���뵽һ�ſ���������Ԫ�س�Ϊ����
    t = malloc(sizeof(BinNode));
    t->v = x;
    t->left = t->right = NULL;
    t->flag = 0;
    return t;
  }
  if (x > t->v) {
    // ������������
    t->right = Insert(t->right, x);
  } else if (x < t->v) {
    // ������������
    t->left = Insert(t->left, x);
  } else {
    // ��Ԫ�����ظ���ǰ���£�x�Ѿ����ڣ������롣
  }
  return t;
}

// n�����г��ȣ�����n���������β����������
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

// ���x�Ƿ�ɲ��롣
static int Check(BinNode *tr, int x) {
  while (tr) {
    if (x != tr->v) {
      // ��;�ڵ㡣
      if (!tr->flag)
        return 0;
      tr = x > tr->v ? tr->right : tr->left;
    } else {
      if (tr->flag) {
        // �Ѿ��д�Ԫ��
        return 0;
      }
      tr->flag = 1;
      return 1;
    }
  }
  // ���޴��ˡ�
  return 0;
}

int a[MAXM];

// ����n�������ж����������Ƿ�ȼۡ�
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

// ��flagȫ����Ϊ0.
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
  // �Ե�һ�����н�����
  tr = BuildTree(M);
  for (i = 1; i < N; ++i) {
    int res = Judge(tr, M);
    puts(res ? "Yes" : "No");
    Reset(tr);
  }
}
