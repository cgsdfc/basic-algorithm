/*
层序遍历，即广度优先遍历。
要先实现队列操作。
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

// 队列节点。 
typedef struct QNode {
	ElemType data;
	struct QNode* next;
} QNode;

typedef struct LinkQueue {
	QNode* front;
	QNode* rear;
	int size; // 增加size，使得层序遍历时能获取当前层次的所有节点。 
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
	// 尾插法。 
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
层序遍历以node为根的二叉树，
*/ 
void LevelOrderTraversal(Node* node) {
	Queue q;
	
	q=Create();
	PushQueue(q, node);
	while (!Empty(q)) {
		/*
		每次循环到达这里，队列里面的全部元素都是同一层次的。
		因此逐一取出当前size数量的元素，它们属于同一层。
		*/ 
		node=PopQueue(q);
		// 处理node
		if (node->left) {
			PushQueue(q, node->left);
		}
		if (node->right) {
			PushQueue(q, node->right);
		}
	}
}

/*
对每一层进行遍历。
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
			// node是第level层的第i个节点。
			// 这样就实现了对树的先行后列的遍历。 
			node=PopQueue(q);
			// 处理node
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
层序建树。
输入格式是层序的，即
3
1
2 3
4 5 6 -1
要求建树。数字表示节点的值，-1表示空节点。
第一个数字表示有多少行。 
*/ 
Node* LevelBuildTree(void) {
	int n; // n 行数据。 
	int i;
	Node* root; // 最后要返回的，不能破坏。 
	int v;
	Queue q;
	
	scanf("%d",&n);
	q=Create();
	scanf("%d", &v);
	root=NewNode(v);
	PushQueue(q, root);
	
	/*
	处理每一行数据。
	*/ 
	for (i=1;i<n;++i) {
		int j;
		int size;
		
		/*
		第i次应输入 2^i个数据，从队列弹出2^i-1个节点，
		每两个相邻的数据，成为一个弹出的节点的两个孩子，然后再把两个孩子入队。
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
只有同时打印中序和后序序列，才能确定一个二叉树。
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

