#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 105
struct Node {
	int data;
	int lchild,rchild;
} node[MAXN];

int index;
int NewNode(int v) {
	node[index].data=v;
	node[index].lchild=node[index].rchild=-1;
	return index++;
}

void Init() {
	index=0;
}

void Insert(int& root, int x) {
	if (root == -1) {
		root=NewNode(x);
		return;
	}
	// 注意：重复元素不要插入，直接丢弃！！ 
	if (x == node[root].data) {
		return;
	}
	if (x < node[root].data) {
		Insert(node[root].lchild, x);
	} else {
		Insert(node[root].rchild, x);
	}
}

int Create(int N) {
	int root=-1;
	for (int i=0;i<N;++i) {
		int x;
		scanf("%d", &x);
		Insert(root, x);
	}
	return root;
}

enum Ord {
	PRE,IN,POST,
};

void Print(int root) {
	printf("%d ", node[root].data);
}

void DFS(int root, Ord order) {
	if (root != -1) {
		if (order == PRE) Print(root);
		DFS(node[root].lchild, order);
		if (order == IN) Print(root);
		DFS(node[root].rchild, order);
		if (order == POST) Print(root);
	}
}

int main(int argc, char** argv) {
		int N;
	while (scanf("%d", &N) != EOF) {
		Init();
		int root=Create(N);
		for (int i=0;i<3;++i) {
			DFS(root, (Ord)i);
			printf("\n");
		}
	}
	return 0;
}
