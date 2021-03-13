#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZE 100

// 用一个数组，实现两个栈，要求只要数组还有空间，Push操作就能成功。

typedef struct DStack {
	int data[MAXSIZE];
	int top1;
	int top2;
}* DStack;

static
DStack Create(void) {
	DStack s=malloc(sizeof(DStack));
	s->top1=-1;
	s->top2=MAXSIZE;
	memset(&s->data, 0, sizeof(s->data));
	return s;
}

// tag==1 表示第一个栈，其他表示第二个栈。 
static
int IsEmpty(DStack s, int tag) {
	if (tag==1) {
		return s->top1==-1;
	} else {
		return s->top2==MAXSIZE;
	}
}

static
void Push(DStack s, int item, int tag) {
	if (s->top2 - s->top1 == 1) {
		printf("OverflowError");
		return;
	}
	if (tag==1) {
		s->data[++(s->top1)]=item;
	} else {
		s->data[--(s->top2)]=item;
	}
}

static
int Pop(DStack s, int tag) {
	if (IsEmpty(s, tag)) {
		printf("UnderflowError");
		return -1;
	}
	if (tag==1) {
		return s->data[s->top1--];
	} else {
		return s->data[s->top2++];
	}
}

void TestDoubleStack(void) {
	DStack s;
	int i;
	
	s=Create();
	
	for (i=0;i<10;++i) {
		printf("%d\n",i);
		Push(s, i, 1);
		Push(s, i, 2);
	}
	return;
	
	while (!IsEmpty(s, 1)) {
		printf("%d\n", Pop(s, 1));
	}
	while (!IsEmpty(s, 2)) {
		printf("%d\n", Pop(s, 2));
	}
}
