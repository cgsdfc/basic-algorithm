#include <cstdio>
#include <algorithm>
//using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 1005

// 注意，stl里面有个count符号。 
int count[MAXN]; // 每个节点为根的子树的节点数。
int tree[MAXN]; // 保存完全BST。
int data[MAXN]; // 节点数据域。 

// 完全二叉树的中序，元素是下标。 
struct {
	int data[MAXN];
	int len;
} in;

int N; // 节点数。
 
int lchild(int x) {
	return 2*x;
}
int rchild(int x) {
	return 2*x+1;
}

// O(N) 求所有子树的节点数。 
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
	int k=inL+numL; // 根节点数据的位置。 
	tree[root]=data[k];
	Create(lchild(root), inL, k-1);
	Create(rchild(root), k+1, inR);
}

/*
注意完全二叉树的根节点标号为1，
最后一个节点标号为N，故下标从1--N。
*/
 
/*
用后面《Build a Binary Search Tree》的方法：
中序遍历N个元素的完全二叉树，然后用键值的中序遍历与之对应，
就得出了键值对应的节点下标。
这个方法不用求子树大小，也不用中序建树。
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
	// 排序就得到中序。 
	std::sort(data+1, data+N+1);
	// 计算各子树的大小。 
//	DFS(1);
	
//	for (int i=1;i<=N;++i) {
//		printf("%d\n", count[i]);
//	}
	// 从 count 和 data 重建二叉树。 
//	Create(1, 1, N);

	// 中序遍历。
	in.len=1; // 下标从1开始，要统一。 
	Inorder(1);
	// 现在in和data两个数组的元素具有一一对应。
	// in[i] 表示 data[i] 所在的节点下标。 
	for (int i=1;i<=N;++i) {
		tree[in.data[i]]=data[i];
	}
	for (int i=1;i<=N;++i) {
		printf("%d%s", tree[i], i==N?"\n":" ");
	}
	return 0;
}
