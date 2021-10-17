#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
};

Node* Create(void) {
    Node* head;
    Node* last;
    int N;

    head = malloc(sizeof(Node));
    last = head;
    scanf("%d", &N);
    while (N--) {
        int x;
        Node* p;

        scanf("%d", &x);
        p = malloc(sizeof(Node));
        p->data = x;
        p->next = NULL;  // β�巨��ע��ÿ���½ڵ��next��
        last->next = p;
        last = p;
    }
    // ע����ѭ������
    last->next = head;
    return head;
}

void Show(Node* head) {
    Node* p = head->next;
    // ע��ѭ������ı߽�������
    while (p != head) {
        printf("%d%s", p->data, p->next != head ? " " : "\n");
        p = p->next;
    }
}

Node* Merge(Node* a, Node* b) {
    Node* p = a->next;
    // �ҵ�a�����һ��Ԫ�ء�
    while (p->next != a) {
        p = p->next;
    }
    p->next = b->next;
    p = b->next;
    while (p->next != b) {
        p = p->next;
    }
    p->next = a;
    free(b);
    return a;
}

/*
��Ҫβ�������Ļ������İ취�Ǳ���β��ָ�� last��
*/

int main(int argc, char* argv[]) {
    Node* a;
    Node* b;

    a = Create();
    b = Create();
    a = Merge(a, b);
    Show(a);

    return 0;
}
