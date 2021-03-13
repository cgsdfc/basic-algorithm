/*
�����������������ȱ�����
Ҫ��ʵ�ֶ��в�����
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node Node;
struct Node {
	int data;
	Node* left;
	Node* right;
}; 

typedef Node* ElemType;

// ���нڵ㡣 
typedef struct QNode {
	ElemType data;
	struct QNode* next;
} QNode;

typedef struct LinkQueue {
	QNode* front;
	QNode* rear;
	int size; // ����size��ʹ�ò������ʱ�ܻ�ȡ��ǰ��ε����нڵ㡣 
}* Queue;

static
Queue Create(void) {
	Queue q=malloc(sizeof(struct LinkQueue));
	q->front=q->rear=NULL;
	q->size=0;
	return q;
}

static
int Empty(Queue q) {
	return q->front==NULL;
}

static
void PushQueue(Queue q, ElemType item) {
	// Allocate a node first.
	QNode* n=malloc(sizeof(QNode));
	n->data=item;
	n->next=NULL;
	++q->size;
	// β�巨�� 
	if (Empty(q)) {
		q->front = q->rear = n;
	} else {
		q->rear->next=n;
		q->rear=n;
	}
}

static
ElemType PopQueue(Queue q) {
	QNode* n;
	ElemType item;
	
	assert(!Empty(q));
	n = q->front;
	item = n->data;
	--q->size;
	if (q->front == q->rear) {
		// Only one element. After pop, will be empty.
		q->front=q->rear=NULL;
	} else {
		q->front=n->next;
	}
	free(n);
	return item;
}

static
int Size(Queue q) {
	return q->size;
}

/*
���������nodeΪ���Ķ�������
*/ 
void LevelOrderTraversal(Node* node) {
	Queue q;
	
	q=Create();
	PushQueue(q, node);
	while (!Empty(q)) {
		/*
		ÿ��ѭ������������������ȫ��Ԫ�ض���ͬһ��εġ�
		�����һȡ����ǰsize������Ԫ�أ���������ͬһ�㡣
		*/ 
		node=PopQueue(q);
		// ����node
		if (node->left) {
			PushQueue(q, node->left);
		}
		if (node->right) {
			PushQueue(q, node->right);
		}
	}
}

/*
��ÿһ����б�����
*/ 
void LevelOrderTraversal2(Node* node) {
	Queue q;
	int level=0;
	
	q=Create();
	PushQueue(q, node);
	while (!Empty(q)) {
		int size=Size(q);
		int i;
		
		++level;
		for (i=0;i<size;++i) {
			// node�ǵ�level��ĵ�i���ڵ㡣
			// ������ʵ���˶��������к��еı����� 
			node=PopQueue(q);
			// ����node
			if (node->left) {
				PushQueue(q, node->left);
			}
			if (node->right) {
				PushQueue(q, node->right);
			}
		}
	}
}

static
Node* NewNode(int v) {
	Node* node=malloc(sizeof(Node));
	node->data=v;
	node->left=node->right=NULL;
	return node;
}

/*
��������
�����ʽ�ǲ���ģ���
3
1
2 3
4 5 6 -1
Ҫ���������ֱ�ʾ�ڵ��ֵ��-1��ʾ�սڵ㡣
��һ�����ֱ�ʾ�ж����С� 
*/ 
Node* LevelBuildTree(void) {
	int n; // n �����ݡ� 
	int i;
	Node* root; // ���Ҫ���صģ������ƻ��� 
	int v;
	Queue q;
	
	scanf("%d",&n);
	q=Create();
	scanf("%d", &v);
	root=NewNode(v);
	PushQueue(q, root);
	
	/*
	����ÿһ�����ݡ�
	*/ 
	for (i=1;i<n;++i) {
		int j;
		int size;
		
		/*
		��i��Ӧ���� 2^i�����ݣ��Ӷ��е���2^i-1���ڵ㣬
		ÿ�������ڵ����ݣ���Ϊһ�������Ľڵ���������ӣ�Ȼ���ٰ�����������ӡ�
		*/ 
		size=Size(q);
		assert((1<<(i-1)) == size); 
		
		for (j=0;j<size;++j) {
			int left,right;
			Node* node;
			
			node=PopQueue(q);
			scanf("%d%d",&left,&right);
			if (left != -1) {
				node->left=NewNode(left);
				PushQueue(q, node->left);
			}
			if (right != -1) {
				node->right=NewNode(right);
				PushQueue(q, node->right);
			}
			
		}
	}
	return root;
}

static
void PrintTree2(Node* node, int ord) {
	if (node) {
		if (ord == 1)
			printf("%d ", node->data);
		PrintTree2(node->left,ord);
		if (ord == 2) {
			printf("%d ", node->data);
		}
		PrintTree2(node->right,ord);
		if (ord == 3) {
			printf("%d ", node->data);
		}
	}
}

/*
ֻ��ͬʱ��ӡ����ͺ������У�����ȷ��һ����������
*/ 
static
void PrintTree(Node* node) {
	PrintTree2(node, 1);
	putchar('\n');
	PrintTree2(node, 2);
	putchar('\n');
}

void TestLevelBuildTree(void) {
	Node* root;
	
	root=LevelBuildTree();
	PrintTree(root);
}

