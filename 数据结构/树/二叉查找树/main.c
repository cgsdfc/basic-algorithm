#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
�����������BST���Ĳ�����ʵ�֡�
1. ���Ҹ���Ԫ�ء�
2. �������ֵ����Сֵ��
3. ����Ԫ�أ��ǽ����Ļ�����������
4. ɾ��Ԫ�ء�
*/

typedef struct BinNode BinNode;
struct BinNode {
  int v;
  BinNode *left, *right;
};

/*
����tΪ�������в���x���ҵ��򷵻ر���x�Ľڵ㣬���򷵻�NULL��
*/
BinNode *Find(BinNode *t, int x) {
  if (!t)
    return NULL; // �����ض�����ʧ�ܡ�
  /*
  ��t->vΪ·�꣬��xС����ʱ������߼����ң���x����taʱ�����ұ߼����ҡ�
  */
  if (x < t->v) {
    return Find(t->left, x);
  } else if (x > t->v) {
    return Find(t->right, x);
  } else {
    // Ҫ�ҵ�x�����ڸ���
    return t;
  }
}

/*
�������Find���Ͷ��ֲ������ƣ��Ƚ�����ʵ�֣����Ҹ��Ӹ�Ч��
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
������СԪ�ض�Ӧ�Ľڵ㣬��������NULL��
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
�������Ԫ�ض�Ӧ�Ľڵ㣬��������NULL��
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
�ݹ�ʵ��FindMax����ʵFind��FindMax����β�ݹ飬�����õ���ʵ�֡�
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
���������t�Ǳ���������ĸ���x����Ԫ�ء����ز����������ĸ���
������ƽ����������²���Ľڵ����ǳ�ΪҶ�ڵ㡣
*/
BinNode *Insert(BinNode *t, int x) {
  if (!t) {
    // ���뵽һ�ſ���������Ԫ�س�Ϊ����
    t = malloc(sizeof(BinNode));
    t->v = x;
    t->left = t->right = NULL;
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

/*
����tΪ��������ɾ��x��Ӧ��Ԫ�أ�����ɾ��������ĸ���
*/
BinNode *Delete(BinNode *t, int x) {
  if (!t) {
    // �����޷�ɾ���κ�Ԫ�ء�
    // ���ֿ���˵��Ԫ���Ҳ�����
    printf("NotFound\n");
    return NULL;
  }
  // �ȵݹ��ҵ�Ҫɾ���Ľڵ�λ�á�
  if (x < t->v) {
    // Ҫɾ��Ԫ������������ɾ���t����������
    t->left = Delete(t->left, x);
  } else if (x > t->v) {
    t->right = Delete(t->right, x);
  } else {
    // �ҵ���x��Ӧ�Ľڵ㡣
    /*
    ��Ϊ���������
    1. t��Ҷ�ӽڵ㣬��ֱ��free������NULL���ظ��ϲ㡣
    2. tֻ��һ�����ӣ����t��Ψһ���ӹҵ�t�ĸ��ڵ㣬ɾ��t��
    3. t���������ӣ�����������ҵ����ֵ����������������Сֵ��m��
            ��m����t��ֵ��Ȼ���m��Ӧ�Ľڵ�ɾ������Ϊm�����ֵ����Сֵ���ڵ㣬
            �ض����Թ�Ϊ1��2�����
    */

    // ���3
    if (t->left && t->right) {
      // �������������ֵ����������������Сֵ��
      BinNode *tmp = FindMax(t->left);
      assert(tmp);
      // �����ֵ����t��ֵ��
      t->v = tmp->v;
      // ����������ɾ��tmp
      t->left = Delete(t->left, tmp->v);
    } else {
      // t��һ��Ҫfree�ģ��ڴ�֮ǰ���ȱ������ķǿյĺ��ӣ�����NULL����
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
������������һ�������У���˳�����Ԫ�ؽ���һ������
*/
BinNode *BuildTree(int a[], int n) {
  int i;
  BinNode *t = NULL; // ��ʼ��һ�������������ʼ����

  for (i = 0; i < n; ++i) {
    t = Insert(t, a[i]);
  }
  return t;
}

/*
�Եݹ鷽ʽ�ͷ���t���ڴ档
ע�⣬���ú��������
*/
void FreeTree(BinNode *t) {
  if (t) {
    FreeTree(t->left);
    FreeTree(t->right);
    free(t);
  }
}

/*
�����ű��ʽ��ӡ��������
���� (a (b) (c)) ��
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
