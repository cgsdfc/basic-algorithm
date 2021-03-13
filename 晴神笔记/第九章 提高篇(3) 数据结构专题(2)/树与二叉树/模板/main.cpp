#include <iostream>
#include <cassert>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
������ͨ��ģ��
*/

/*
������������ṹ��
*/ 
struct Node {
	int data;
	Node* lchild; // left
	Node* rchild; // right
}; 

// �½��ڵ㡣 
Node* newNode(int v) {
	Node* p=new Node;
	p->data=v;
	p->lchild=p->rchild=NULL; // ���к���Ҫ��
	return p; 
}

// �������������x�Ľڵ㣬���������޸�Ϊnewdata�� 
void search(Node* root, int x, int newdata) {
	if (!root) {
		return; // ����Ϊ�ݹ�߽磨һ�㣩�� 
	}
	if (root->data == x) {
		// ���ҳɹ���
		root->data=newdata; 
	}
	// �����޸�����������������
	search(root->lchild, x, newdata);
	search(root->rchild, x, newdata);
}

/*
�������Ĳ���������������ʶ��졣
����һ��Ľ����ǣ�
����λ�þ��ǲ���ʧ�ܵ�λ�á�
������ʧ�ܵ�λ�þ�����󵽴������
������ҳɹ������Ƿ���в��룬����Ŀ����˼������
 
ע�⣬����������Ҫ�޸�rootָ����Ԫ�أ����Ա�����
���á� 

root��������
x����Ԫ�ص����ݡ� 
*/ 
void insert(Node*& root, int x) {
	if (!root) {
		// ����ʧ�ܣ��������λ�ã��߽磩��
		root=newNode(x);
		return; 
	}
	if (/* �ɶ����������ʣ�xӦ�ò���������*/1) {
		insert(root->lchild, x);
	} else {
		insert(root->rchild, x);
	}
}

/*
�������õģ��ʺ�C���Եİ汾��
���ص��ǲ��������ĸ������÷�����ѷ���ֵ�������ʵ�λ�ã�
���磺

	Node* root=NULL;
	for (x in array) {
		 root=insert(root, x);
	}
	
*/ 

Node* insert2(Node* root, int x) {
	if (!root) {
		// �������룬�����¸���
		return newNode(x); 
	}
	if (/* �ɶ����������ʣ�xӦ�ò���������*/1) {
		// ���������������������� 
		root->lchild=insert2(root->lchild, x);
	} else {
		root->rchild=insert2(root->rchild, x);
	}
	// �ǵ÷��ء� 
	return root;
}

/*
���������������ϲ���ڵ㡣
�����������飬��Ҳ���Ա�����߲��롣 
*/
Node* Create(int data[], int len) {
	Node* root=NULL;
	for (int i=0;i<len;++i) {
		insert(root, data[i]);
//		root=insert2(root, data[i]);
	}
	return root;
} 

/*
��ȫ������
*/
// ����Ĵ�С���Ͻ�Ϊ�ڵ�����
// ���ֻ֪�����߶�K�����Ͻ�Ϊ (1<<K)�� 
#define MAXN 100

struct Tree {
	int data[MAXN]; // ���������� 
	int N; // �ڵ�����ע��������Ч����Ϊ N+1��
	// ��Ϊ0�ſ��ã�1--N �ֱ𱣴������кϷ��ڵ㡣 
	
	void Print() {
		for (int i=1;i<=N;++i) {
			printf("%d ", data[i]);
		}
		printf("\n");
	}
	bool Has(int i) {
		// �ж�ĳ���Ƿ�Ϊ�Ϸ��ڵ㡣
		return 1<=i&&i<=N; 
	}
	// ���ӵı�š� 
	int lchild(int i) {
		return 2*i;
	}
	// �Һ��ӵı�š� 
	int rchild(int i) {
		return 2*i+1;
	}
	// ���׵ı�š� 
	int parent(int i) {
		return i/2;
	}
	bool IsLeaf(int i) {
		// �ж�ĳ���Ƿ�ΪҶ�ڵ㣬ע�⣬Ӧ�ж������Ƿ���ڡ�
		assert(Has(i));
		return Has(lchild(i)); 
	}
	int Root() {
		assert(Has(1));
		// ���ڵ����������1�š�
		return data[1]; 
	}
}; 

int main(int argc, char** argv) {
	return 0;
}
