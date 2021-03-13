#include <iostream>
#include <queue>
using namespace std;
 
/*
二叉树的四种遍历的模板。
*/
typedef int Elem;
struct Node {
	Elem data;
	Node* left;
	Node* right;
	int layer;
	
};

// 层序遍历，即二叉树的BFS。 
void LayerOrder(Node* root) {
	if (!root) {
		return; // 空树。 
	}
	root->layer=1; // 记得把根的层次先标定，否则后面标定其他节点的层次会出错。 
	queue<Node*> Q;
	Q.push(root);
	/*
	注意，因为树是无环的，所以不需要 inq，每个节点不可能
	重复入队。
	*/
	while (!Q.empty()) {
		Node* now=Q.front(); // 当前元素可以命名为 now
		Q.pop();
		printf("data %d layer %d\n", now->data, now->layer);
		// 注意，先左后右的访问子节点。 
		if (now->left) {
			now->left->layer=now->layer+1;
			Q.push(now->left);
		} 
		// 注意不要把NULL放进队列。 
		if (now->right) {
			now->right->layer=now->layer+1;
			Q.push(now->right);
		}
	} 
}

// 先序遍历，即树的DFS。
void Preorder(Node* root) {
	/*
	注意，DFS和BFS的判空的不同，
	DFS是一上来在函数开头判空；
	BFS是入队之前判空。
	*/ 
	if (!root) return;
	printf("data %d\n", root->data);
	Preorder(root->left);
	Preorder(root->right);
} 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	return 0;
}
