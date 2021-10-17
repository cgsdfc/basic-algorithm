#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef Node* Stack;

// Create an empty stack.
static Stack CreateStack(void) {
    Stack s = (Node*) malloc(sizeof(Node));
    s->next = NULL;
    s->data = 0;
    return s;
}

static int IsEmpty(Stack s) {
    return s->next == NULL;
}

static void Push(Stack s, int item) {
    Node* n = malloc(sizeof(Node));
    n->data = item;
    n->next = s->next;
    s->next = n;
}

static int Pop(Stack s) {
    if (IsEmpty(s)) {
        printf("UnderflowError");
        return -1;
    }
    Node* top = s->next;
    int data = top->data;
    s->next = top->next;
    free(top);
    return data;
}

static int Top(Stack s) {
    return IsEmpty(s) ? -1 : s->next->data;
}

void TestLinkStack(void) {
    Stack s;
    int i;

    s = CreateStack();
    for (i = 0; i < 10; i++) {
        Push(s, i);
    }
    while (!IsEmpty(s)) {
        int data = Pop(s);
        printf("%d\n", data);
    }
}
