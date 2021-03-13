#include <iostream>
#include <queue>
using namespace std;
 
/*
�����������ֱ�����ģ�塣
*/
typedef int Elem;
struct Node {
	Elem data;
	Node* left;
	Node* right;
	int layer;
	
};

// �������������������BFS�� 
void LayerOrder(Node* root) {
	if (!root) {
		return; // ������ 
	}
	root->layer=1; // �ǵðѸ��Ĳ���ȱ궨���������궨�����ڵ�Ĳ�λ���� 
	queue<Node*> Q;
	Q.push(root);
	/*
	ע�⣬��Ϊ�����޻��ģ����Բ���Ҫ inq��ÿ���ڵ㲻����
	�ظ���ӡ�
	*/
	while (!Q.empty()) {
		Node* now=Q.front(); // ��ǰԪ�ؿ�������Ϊ now
		Q.pop();
		printf("data %d layer %d\n", now->data, now->layer);
		// ע�⣬������ҵķ����ӽڵ㡣 
		if (now->left) {
			now->left->layer=now->layer+1;
			Q.push(now->left);
		} 
		// ע�ⲻҪ��NULL�Ž����С� 
		if (now->right) {
			now->right->layer=now->layer+1;
			Q.push(now->right);
		}
	} 
}

// ���������������DFS��
void Preorder(Node* root) {
	/*
	ע�⣬DFS��BFS���пյĲ�ͬ��
	DFS��һ�����ں�����ͷ�пգ�
	BFS�����֮ǰ�пա�
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
