#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
	int data;
	Node* left;
	Node* right;
};

/*
��������ȡ�
1. L(T)=0 if T is empty.
2. Otherwise, L(T) = 1 + max{L(T.L), L(T.R)}.
*/
static int Max(int a, int b) {
	return a>b?a:b;
}

int TreeDepth2(Node* node) {
	return node?(1+Max(TreeDepth2(node->left), TreeDepth(node->right))):0;
}

int TreeDepth(Node* node) {
	if (node) {
		int left=TreeDepth(node->left);
		int right=TreeDepth(node->right);
		return 1 + (left > right ? left : right);
	} else {
		return 0;
	}
}

/*
��ͬ���ж���
1. �κο�������ͬ���ġ�
2. ���ڷǿ��������ڵ��ֵ��ͬ���������������ֱ��Ӧͬ����
���߽�������������˳��󣬶�Ӧͬ����
3. �κο�����ǿ������ǲ�ͬ���ġ� 
*/

int Similar(Node* a, Node* b) {
	// ����ͬ���� 
	if (!a && !b) return 1;
	if ((a && !b) || (!a && b)) return 0;
	// a��b���ǿ��ˡ�
	if (a->data != b->data) return 0;
	// ���ý�������Ӧ����ͬ���� 
	if (Similar(a->left, b->left) && Similar(a->right, b->right)) return 1;
	// ���������󣬶�Ӧͬ���� 
	return Similar(a->left, b->right) && Similar(a->right, b->left);
}

