#include <cstdio>
#include <algorithm>
//using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 1005

// ע�⣬stl�����и�count���š� 
int count[MAXN]; // ÿ���ڵ�Ϊ���������Ľڵ�����
int tree[MAXN]; // ������ȫBST��
int data[MAXN]; // �ڵ������� 

// ��ȫ������������Ԫ�����±ꡣ 
struct {
	int data[MAXN];
	int len;
} in;

int N; // �ڵ�����
 
int lchild(int x) {
	return 2*x;
}
int rchild(int x) {
	return 2*x+1;
}

// O(N) �����������Ľڵ����� 
int DFS(int root) {
	if (root > N) {
		return 0;
	}
	int ans=1+DFS(lchild(root))+DFS(rchild(root));
	count[root]=ans;
	return ans;
} 

void Create(int root, int inL, int inR) {
	if (root > N || inL > inR) {
		return;
	}
	int numL=0;
	if (lchild(root) <= N) {
		numL=count[lchild(root)];
	}
	int k=inL+numL; // ���ڵ����ݵ�λ�á� 
	tree[root]=data[k];
	Create(lchild(root), inL, k-1);
	Create(rchild(root), k+1, inR);
}

/*
ע����ȫ�������ĸ��ڵ���Ϊ1��
���һ���ڵ���ΪN�����±��1--N��
*/
 
/*
�ú��桶Build a Binary Search Tree���ķ�����
�������N��Ԫ�ص���ȫ��������Ȼ���ü�ֵ�����������֮��Ӧ��
�͵ó��˼�ֵ��Ӧ�Ľڵ��±ꡣ
�������������������С��Ҳ������������
*/

void Inorder(int root) {
	if (root <= N) {
		Inorder(lchild(root));
		in.data[in.len++]=root;
		Inorder(rchild(root));
	}
}

int main(int argc, char** argv) {
	scanf("%d", &N);
	for (int i=1;i<=N;++i) {
		scanf("%d", &data[i]);
	}
	// ����͵õ����� 
	std::sort(data+1, data+N+1);
	// ����������Ĵ�С�� 
//	DFS(1);
	
//	for (int i=1;i<=N;++i) {
//		printf("%d\n", count[i]);
//	}
	// �� count �� data �ؽ��������� 
//	Create(1, 1, N);

	// ���������
	in.len=1; // �±��1��ʼ��Ҫͳһ�� 
	Inorder(1);
	// ����in��data���������Ԫ�ؾ���һһ��Ӧ��
	// in[i] ��ʾ data[i] ���ڵĽڵ��±ꡣ 
	for (int i=1;i<=N;++i) {
		tree[in.data[i]]=data[i];
	}
	for (int i=1;i<=N;++i) {
		printf("%d%s", tree[i], i==N?"\n":" ");
	}
	return 0;
}
