#include <stdio.h>
#include <stdlib.h>

/*
��ͨ���ļ��ֱ�ʾ������
�Լ����Ļ������ԵĻ�ȡ��

��ʾ������
1. ����-�ֵܱ�ʾ����ÿ���ڵ㱣����һ�����Ӻ���һ���ֵܵ�ָ�롣
2. ���ӱ�ʾ����ÿ���ڵ㱣�����к��ӵ�ָ�롣
3. ��̬���飬����1�б�ʾ���þ�̬�����ʾ��

�������ԣ�
1. ���Ľڵ�����N��
        N=0����Ϊ�������������нڵ㼴�ɻ�ȡ������ά��size������

2. �ڵ�Ķȣ����ڽڵ�ĺ�������

3. ���Ķȣ������нڵ�Ķȵ����ֵ��

4. �ڵ�Ĳ�Σ����ڵ��ڵ�һ�㣬�����ڵ�Ĳ�����丸�ڵ��μ�1.
5. ������ȣ��������нڵ������Ρ�
6. ���ıߵ��������ڽڵ�������1.
*/

typedef struct Node Node;
struct Node {
  int data;
  Node *child; // ��һ������
  Node *sibl;  // ��һ���ֵܡ�
};

// �ڵ�ĶȾ��Ǻ�������
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
�ж�һ�����Ƿ�Ϊ�ա�
*/
int IsEmpty(Node *n) { return 0 == NodeCount(n); }
