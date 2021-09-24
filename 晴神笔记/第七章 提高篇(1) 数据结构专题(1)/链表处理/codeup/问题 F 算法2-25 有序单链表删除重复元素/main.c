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
删除递增链表的重复元素。
新链表为New， 原链表为Old，New采用尾插法。
扫描Old，若当前元素不等于New的尾部元素，则Append到New。
*/
void Unique(Node *head) {
  /*
  原地删除重复元素，要求head有序，
  重复元素只保留一份，其他的free掉。
  */
  Node *p;    // 扫描原链表。
  Node *last; // 尾插法插入新链表。

  if (!head->next) {
    // 空链表。
    return;
  }
  // last 取第一个元素。
  last = head->next;
  // p 从last的下一个开始。
  p = last->next;
  while (p) {
    if (p->data != last->data) {
      // 新元素。
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
  head->next = NULL; // 空链表。
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
