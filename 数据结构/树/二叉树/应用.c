#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node {
	int data;
	Node* left;
	Node* right;
};

/*
求树的深度。
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
树同构判定。
1. 任何空树都是同构的。
2. 对于非空树，根节点的值相同，并且两个子树分别对应同构，
或者交换子树的左右顺序后，对应同构。
3. 任何空树与非空树都是不同构的。 
*/

int Similar(Node* a, Node* b) {
	// 空树同构。 
	if (!a && !b) return 1;
	if ((a && !b) || (!a && b)) return 0;
	// a和b都非空了。
	if (a->data != b->data) return 0;
	// 不用交换，对应子树同构。 
	if (Similar(a->left, b->left) && Similar(a->right, b->right)) return 1;
	// 交换子树后，对应同构。 
	return Similar(a->left, b->right) && Similar(a->right, b->left);
}

