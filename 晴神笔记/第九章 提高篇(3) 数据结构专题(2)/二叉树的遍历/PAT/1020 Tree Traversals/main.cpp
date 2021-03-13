#include <cstdio>
#include <queue> // BFS.
using namespace std;

/*
�����������Ȼ����������
*/
#define MAXN 35

struct Node {
	int data;
	int lchild;
	int rchild;
};

// ��̬�������� 
Node node[MAXN];
// ��ǰ���õĽڵ��š� 
int index;

int newNode(int v) {
	node[index].data=v;
	node[index].lchild=node[index].rchild=-1;
	return index++;	
}

int in[MAXN], post[MAXN];
// ���� post��Ȼ�� in��
int N; // �ڵ�����

void Read(int a[]) {
	for (int i=0;i<N;++i) {
		scanf("%d", &a[i]);
	}
}

// Node* �� int ���档 
// ������������ͺ������䡣 
int Create(int inL, int inR, int postL, int postR) {
	if (inL > inR) {
		return -1;
	}
	int v=post[postR];
	int root=newNode(v);
	
	int k;
	for (k=inL;k<=inR;++k) {
		if (v == in[k]) {
			break;
		}
	}
	int numL=k-inL;
	node[root].lchild=Create(inL, k-1, postL, postL+numL-1);
	node[root].rchild=Create(k+1, inR, postL+numL, postR-1);
	return root;
}

void BFS(int root) {
	queue<int> Q;
	Q.push(root);
	int i=0;
	
	while (!Q.empty()) {
		int now=Q.front();
		Q.pop();
		printf("%d%s", node[now].data, i==N-1?"\n":" ");
		++i;
		if (node[now].lchild != -1) {
			Q.push(node[now].lchild);
		}
		if (node[now].rchild != -1) {
			Q.push(node[now].rchild);
		}
	}
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	scanf("%d", &N);
	Read(post);
	Read(in);
	int root=Create(0, N-1, 0, N-1);
	BFS(root);
	return 0;
}
