#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
对于链表来说，如果使用二分查找，则复杂度是nlogn，
因为每次要用n来找到中点，然后进行logn次，所以上界是nlogn。
所以还不如顺序查找。
*/

typedef struct Node Node;
struct Node {
  int data;
  Node *next;
};

// 带头节点，尾插法。
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
在有序链表中查找第一个大于等于x的元素。
如果存在，并且该元素等于x，则该元素与其后继交换（交换data即可）。
否则，将x插入到该位置。
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
    assert(p->next); // 题目保证此时后继存在。
    p->data = p->next->data;
    p->next->data = x;
    return 1;
  }
  // p就是插入位置，因为p的前驱必定小于x，而p大于等于x。
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
