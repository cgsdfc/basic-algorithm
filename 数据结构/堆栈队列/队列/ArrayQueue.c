#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
用顺序表（静态数组）实现的队列。 
当队列最大长度已知时，使用静态数组比较方便。
当一定要动态扩展时，比如元素上限非常大，或者使用静态数组不通过时，
可换成链表实现，只要保持基本操作函数签名不变即可。
*/

#define MAXSIZE 10

/*
实现顺序表队列时，重点注意队列满和队列空两种状态的区分。
有两种方法：
1. 用 size 变量记录队列长度，size==0 则队列空，size==MAXSIZE 则队列满。
2. 在 front 和 rear 之间保留一个空位不放元素，则 rear==front 时队列空，
(rear+1) % MAXSIZE == front 时队列满。 
方法一可以得知队列长度，方法二只能得知队列是空是满。
 
另外要注意 front 和 rear 的意义。front 指向队头的前一个元素，rear 指向队尾元素。
初始时令 front = rear = -1 。 

用链表队列时，没有队列满的问题，队列空则是一般的链表空。 
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
	front和rear的初值不能是-1，因为当front==-1，而rear>=0时，(rear+1) % MAXSIZE 
	恒为整数，所以Full恒不成立。这样判断队满的逻辑就失效了。 
	空出来的元素是data[0]。 
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
	// 见王道数据结构P79
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
