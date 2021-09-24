#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
����������˵�����ʹ�ö��ֲ��ң����Ӷ���nlogn��
��Ϊÿ��Ҫ��n���ҵ��е㣬Ȼ�����logn�Σ������Ͻ���nlogn��
���Ի�����˳����ҡ�
*/

typedef struct Node Node;
struct Node {
  int data;
  Node *next;
};

// ��ͷ�ڵ㣬β�巨��
Node *Create(void) {
  Node *head;
  Node *last;
  int N;

  head = last = malloc(sizeof(Node));
  scanf("%d", &N);
  while (N--) {
    Node *p = malloc(sizeof(Node));
    int x;
    scanf("%d", &x);
    p->data = x;
    p->next = NULL;
    last->next = p;
    last = p;
  }
  return head;
}

void Print(Node *head) {
  Node *p = head->next;
  while (p) {
    printf("%d%s", p->data, p->next ? " " : "\n");
    p = p->next;
  }
}

/*
�����������в��ҵ�һ�����ڵ���x��Ԫ�ء�
������ڣ����Ҹ�Ԫ�ص���x�����Ԫ�������̽���������data���ɣ���
���򣬽�x���뵽��λ�á�
*/
int LowerBound(Node *head, int x) {
  Node *p = head->next;
  Node *pre = head;

  // lower bound
  while (p && p->data < x) {
    pre = p;
    p = p->next;
  }

  if (p && p->data == x) {
    assert(p->next); // ��Ŀ��֤��ʱ��̴��ڡ�
    p->data = p->next->data;
    p->next->data = x;
    return 1;
  }
  // p���ǲ���λ�ã���Ϊp��ǰ���ض�С��x����p���ڵ���x��
  assert(pre);
  p = malloc(sizeof(Node));
  p->data = x;
  p->next = pre->next;
  pre->next = p;
  return 0;
}

int main(int argc, char *argv[]) {
  int x;
  int ans;
  Node *head;

  scanf("%d", &x);
  head = Create();
  ans = LowerBound(head, x);
  puts(ans ? "yes" : "no");
  Print(head);

  return 0;
}
