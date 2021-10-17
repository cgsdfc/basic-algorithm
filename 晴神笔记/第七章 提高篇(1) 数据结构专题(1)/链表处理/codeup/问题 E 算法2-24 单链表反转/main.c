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
    ����ջ��ԭ��ת����
    ���������ϳ�ջ�������������ջ��
    �����������������������ķ�ת��
    */
    Node* temp;
    Node* p;

    /*
    ��ͷ�ڵ�ȡ����������һ���յ�ջ��
    ԭ����Ԫ�ص�������ջ��
    */
    p = head->next;
    temp = head;
    temp->next = NULL;
    while (p) {
        // ��ջ��
        Node* top = p;
        p = p->next;
        // ��ջ��
        top->next = temp->next;
        temp->next = top;
    }
    // ԭ�ط�תhead������
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

// �����ж��飬��ֹ�ڴ治����
void Free(Node* head) {
    Node* p = head;
    while (p) {
        head = p->next;
        free(p);
        p = head;
    }
}

int main(int argc, char* argv[]) {
    int N;  // �����С��
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
