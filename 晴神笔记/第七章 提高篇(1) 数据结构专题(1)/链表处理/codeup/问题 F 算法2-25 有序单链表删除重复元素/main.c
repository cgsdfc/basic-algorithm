#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct Node Node;
struct Node {
  int data;
  Node *next;
};

/*
ɾ������������ظ�Ԫ�ء�
������ΪNew�� ԭ����ΪOld��New����β�巨��
ɨ��Old������ǰԪ�ز�����New��β��Ԫ�أ���Append��New��
*/
void Unique(Node *head) {
  /*
  ԭ��ɾ���ظ�Ԫ�أ�Ҫ��head����
  �ظ�Ԫ��ֻ����һ�ݣ�������free����
  */
  Node *p;    // ɨ��ԭ����
  Node *last; // β�巨����������

  if (!head->next) {
    // ������
    return;
  }
  // last ȡ��һ��Ԫ�ء�
  last = head->next;
  // p ��last����һ����ʼ��
  p = last->next;
  while (p) {
    if (p->data != last->data) {
      // ��Ԫ�ء�
      Node *temp = p->next;
      p->next = NULL;
      last->next = p;
      last = p;
      p = temp;
    } else {
      Node *temp = p->next;
      free(p);
      p = temp;
    }
  }
}

Node *Create(int N) {
  Node *head;
  Node *last;

  head = last = malloc(sizeof(Node));
  head->next = NULL; // ������
  while (N--) {
    Node *p = malloc(sizeof(Node));
    scanf("%d", &p->data);
    p->next = NULL;
    last->next = p;
    last = p;
  }
  return head;
}

void Show(Node *head) {
  while (head = head->next) {
    printf("%d%s", head->data, head->next ? " " : "\n");
  }
}

int main(int argc, char *argv[]) {
  int N;
  Node *head;

  while (scanf("%d", &N) != EOF) {
    if (!N) {
      puts("list is empty");
    } else {
      head = Create(N);
      Show(head);
      Unique(head);
      Show(head);
    }
  }
  return 0;
}
