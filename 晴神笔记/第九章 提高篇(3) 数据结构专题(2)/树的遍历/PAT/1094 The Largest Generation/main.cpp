#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/*
先标定每个节点的level，
同时用散列统计每一个level 的节点数，
最后遍历所有level求最大值即可。
*/

#define MAXN 105

struct Node {
	int level; // 根节点的level=1.
	vector<int> child; 
} node[MAXN];

/*
最大的level是成为一条链时，则为N-1.
*/
int level[MAXN];

int N; // 总节点 
int M; // 非叶节点 
const int root=1;
int MaxLevel;

// 输出最大的level。 
int BFS() {
	queue<int> Q;
	Q.push(root);
	node[root].level=1;
	int ans=-1;
	
	while (!Q.empty()) {
		int now=Q.front();
		Q.pop();
		// 同一个level的人数加一。 
		level[node[now].level]++;
		// 同时求出最大level，这样才可以遍历所有level。 
		if (node[now].level > ans) {
			ans=node[now].level;
		}
		
		for (int i=0;i<node[now].child.size();++i) {
			int p=node[now].child[i];
			Q.push(p);
			node[p].level=node[now].level+1;
		}
	}
	return ans;
	
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	scanf("%d%d", &N, &M);
	for (int i=0;i<M;++i) {
		int p; // 父节点。
		int n; // 孩子数。
		scanf("%d%d", &p, &n);
		while (n--) {
			int c; // 孩子。
			scanf("%d", &c);
			node[p].child.push_back(c); 
		} 
	}
	MaxLevel=BFS();
	int ans=0; // 最大人数。
	int gen; // 对应的代。
	for (int i=1;i<=MaxLevel;++i) {
		if (level[i] > ans) {
			ans=level[i];
			gen=i;
		}
	} 
	printf("%d %d\n", ans, gen);
	
	return 0;
}
