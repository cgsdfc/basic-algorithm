#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
};

void Reverse(Node* head) {
    /*
    利用栈的原理反转链表。
    输入链表不断出栈，输出链表不断入栈，
    则输出链表正好是输入链表的反转。
    */
    Node* temp;
    Node* p;

    /*
    把头节点取出来，当作一个空的栈。
    原来的元素当作满的栈。
    */
    p = head->next;
    temp = head;
    temp->next = NULL;
    while (p) {
        // 出栈。
        Node* top = p;
        p = p->next;
        // 入栈。
        top->next = temp->next;
        temp->next = top;
    }
    // 原地反转head的链表。
}

Node* Create(int N) {
    Node* head;
    Node* last;

    head = last = malloc(sizeof(Node));
    last->next = NULL;
    while (N--) {
        Node* p = malloc(sizeof(Node));
        scanf("%d", &p->data);
        p->next = NULL;
        last->next = p;
        last = p;
    }
    return head;
}

void Show(Node* head) {
    Node* p = head->next;
    while (p) {
        printf("%d%s", p->data, p->next ? " " : "\n");
        p = p->next;
    }
}

// 输入有多组，防止内存不够。
void Free(Node* head) {
    Node* p = head;
    while (p) {
        head = p->next;
        free(p);
        p = head;
    }
}

int main(int argc, char* argv[]) {
    int N;  // 链表大小。
    Node* head;

    while (scanf("%d", &N) != EOF) {
        if (!N) {
            puts("list is empty");
            continue;
        }
        head = Create(N);
        Show(head);
        Reverse(head);
        Show(head);
        Free(head);
    }
    return 0;
}
