#include <iostream>
#include <cassert>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
二叉树通用模板
*/

/*
二叉树的链表结构。
*/ 
struct Node {
	int data;
	Node* lchild; // left
	Node* rchild; // right
}; 

// 新建节点。 
Node* newNode(int v) {
	Node* p=new Node;
	p->data=v;
	p->lchild=p->rchild=NULL; // 这行很重要。
	return p; 
}

// 查找数据域等于x的节点，将其数据修改为newdata。 
void search(Node* root, int x, int newdata) {
	if (!root) {
		return; // 空树为递归边界（一般）。 
	}
	if (root->data == x) {
		// 查找成功。
		root->data=newdata; 
	}
	// 继续修改左子树，右子树。
	search(root->lchild, x, newdata);
	search(root->rchild, x, newdata);
}

/*
二叉树的插入操作因树的性质而异。
但是一般的结论是：
插入位置就是查找失败的位置。
而查找失败的位置就是最后到达空树。
如果查找成功，则是否进行插入，看题目的意思而定。
 
注意，由于最后可能要修改root指向新元素，所以必须用
引用。 

root：树根。
x：新元素的数据。 
*/ 
void insert(Node*& root, int x) {
	if (!root) {
		// 查找失败，即插入的位置（边界）。
		root=newNode(x);
		return; 
	}
	if (/* 由二叉树的性质，x应该插在左子树*/1) {
		insert(root->lchild, x);
	} else {
		insert(root->rchild, x);
	}
}

/*
不用引用的，适合C语言的版本。
返回的是插入后的树的根，调用方必须把返回值赋给合适的位置，
比如：

	Node* root=NULL;
	for (x in array) {
		 root=insert(root, x);
	}
	
*/ 

Node* insert2(Node* root, int x) {
	if (!root) {
		// 空树插入，返回新根。
		return newNode(x); 
	}
	if (/* 由二叉树的性质，x应该插在左子树*/1) {
		// 插入左树，更新左树根。 
		root->lchild=insert2(root->lchild, x);
	} else {
		root->rchild=insert2(root->rchild, x);
	}
	// 记得返回。 
	return root;
}

/*
建树，即往空树上插入节点。
传入数据数组，但也可以边输入边插入。 
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
完全二叉树
*/
// 数组的大小的上界为节点数。
// 如果只知道最大高度K，则上界为 (1<<K)。 
#define MAXN 100

struct Tree {
	int data[MAXN]; // 保存数据域。 
	int N; // 节点数。注意数组有效长度为 N+1。
	// 因为0号空置，1--N 分别保存了所有合法节点。 
	
	void Print() {
		for (int i=1;i<=N;++i) {
			printf("%d ", data[i]);
		}
		printf("\n");
	}
	bool Has(int i) {
		// 判定某号是否为合法节点。
		return 1<=i&&i<=N; 
	}
	// 左孩子的编号。 
	int lchild(int i) {
		return 2*i;
	}
	// 右孩子的编号。 
	int rchild(int i) {
		return 2*i+1;
	}
	// 父亲的编号。 
	int parent(int i) {
		return i/2;
	}
	bool IsLeaf(int i) {
		// 判定某号是否为叶节点，注意，应判定左孩子是否存在。
		assert(Has(i));
		return Has(lchild(i)); 
	}
	int Root() {
		assert(Has(1));
		// 根节点必须在数组1号。
		return data[1]; 
	}
}; 

int main(int argc, char** argv) {
	return 0;
}
