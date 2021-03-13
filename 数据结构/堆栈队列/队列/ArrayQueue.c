#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
��˳�����̬���飩ʵ�ֵĶ��С� 
��������󳤶���֪ʱ��ʹ�þ�̬����ȽϷ��㡣
��һ��Ҫ��̬��չʱ������Ԫ�����޷ǳ��󣬻���ʹ�þ�̬���鲻ͨ��ʱ��
�ɻ�������ʵ�֣�ֻҪ���ֻ�����������ǩ�����伴�ɡ�
*/

#define MAXSIZE 10

/*
ʵ��˳������ʱ���ص�ע��������Ͷ��п�����״̬�����֡�
�����ַ�����
1. �� size ������¼���г��ȣ�size==0 ����пգ�size==MAXSIZE ���������
2. �� front �� rear ֮�䱣��һ����λ����Ԫ�أ��� rear==front ʱ���пգ�
(rear+1) % MAXSIZE == front ʱ�������� 
����һ���Ե�֪���г��ȣ�������ֻ�ܵ�֪�����ǿ�������
 
����Ҫע�� front �� rear �����塣front ָ���ͷ��ǰһ��Ԫ�أ�rear ָ���βԪ�ء�
��ʼʱ�� front = rear = -1 �� 

���������ʱ��û�ж����������⣬���п�����һ�������ա� 
*/

typedef struct QueueImpl {
	int data[MAXSIZE];
	int front;
	int rear;
	// int size; 
}* Queue; 

static
Queue Create(void) {
	Queue q=malloc(sizeof(struct QueueImpl));
	/*
	front��rear�ĳ�ֵ������-1����Ϊ��front==-1����rear>=0ʱ��(rear+1) % MAXSIZE 
	��Ϊ����������Full�㲻�����������ж϶������߼���ʧЧ�ˡ� 
	�ճ�����Ԫ����data[0]�� 
	*/
	q->front=q->rear=0;
	return q;
}

static
int Empty(Queue q) {
	return q->front == q->rear;
}

static
int Full(Queue q) {
	return (q->rear+1) % MAXSIZE == q->front;
}

static
void PushQueue(Queue q, int item) {
	assert(!Full(q));
	q->rear=(q->rear+1)%MAXSIZE;
	q->data[q->rear]=item;
}

static
int PopQueue(Queue q) {
	assert(!Empty(q));
	q->front=(q->front+1)%MAXSIZE;
	return q->data[q->front];
}

static
int Front(Queue q) {
	assert(!Empty(q));
	return q->data[(q->front+1)%MAXSIZE];
}

static
int Rear(Queue q) {
	assert(!Empty(q));
	return q->data[q->rear];
}

static
int Size(Queue q) {
	// ���������ݽṹP79
	return (q->rear - q->front + MAXSIZE) % MAXSIZE; 
}

static
void Print(Queue q) {
	printf("front=%d\n", q->front);
	printf("rear=%d\n", q->rear);
}

void TestArrayQueue(void) {
	int i; 
	Queue q=Create();
	
	assert(Empty(q));
	for (i=1; i<=MAXSIZE-1;++i) {
		PushQueue(q, 1);
	}
	Print(q);
	
	assert(Full(q));
	for (i=1; i<=MAXSIZE-1; ++i) {
		PopQueue(q);
	}
	Print(q);
	
	assert(Empty(q));
	
	for (i=1;i<=3;++i) {
		PushQueue(q, i);
	}
	assert(Size(q) == 3);
	
	for (i=1;i<=3;++i) {
		assert(PopQueue(q) == i);
	}
}
