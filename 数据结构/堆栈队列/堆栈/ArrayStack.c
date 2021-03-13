#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 100

typedef struct ArrayStack {
	int data[MAXSIZE];
	int top;
} *Stack;

static
Stack CreateStack(void) {
	Stack s = malloc(sizeof(struct ArrayStack));
	s->top = -1; // Init empty.
	return s;
}

static
int IsEmpty(Stack s) {
	return s->top == -1;
}

static
void Push(Stack s, int item) {
	if (s->top == MAXSIZE - 1) {
		printf("OverflowError");
		return;
	}
	s->data[++s->top] = item;
}

static
int Pop(Stack s) {
	if (IsEmpty(s)) {
		printf("UnderflowError");
		return -1;
	}
	return s->data[s->top--];
}

static
int Top(Stack s) {
	if (IsEmpty(s)) {
		printf("UnderflowError");
		return -1;
	}
	return s->data[s->top];
}

void TestArrayStack(void) {
	Stack s;
	int i;
	
	s=CreateStack();
	for (i=0;i<10;i++) {
		Push(s, i);
	}
	while (!IsEmpty(s)) {
		int data=Pop(s);
		printf("%d\n", data);
	}
}
