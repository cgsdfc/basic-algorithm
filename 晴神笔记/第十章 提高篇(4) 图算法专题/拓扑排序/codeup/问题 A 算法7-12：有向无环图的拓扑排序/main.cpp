#include <cstdio>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

/*
用Stack模拟拓扑排序算法，本质上用Queue和Stack都一样，（因为算法其实只需要一个结构暂时保存入度为0的节点
进行输出和处理，以免反复扫描全部节点）， 
不同的是部分没有偏序关系的元素的顺序的确定。
*/

#define MAXN 55
bool G[MAXN][MAXN];
int In[MAXN]; // 入度。
int N;

void TopoSort() {
	stack<int> S;
	vector<int> Ans; // 排序的序列。 
	// 节点0--N-1.
	for (int v=0;v<N;++v) {
		if (!In[v]) {
			S.push(v);
		}
	}
	while (!S.empty()) {
		int u=S.top();
		S.pop();
		Ans.push_back(u);
		for (int v=0;v<N;++v) {
			if (G[u][v]) { // u->v
				--In[v];
				if (!In[v]) {
					S.push(v);
				}
			}
		}
	}
	bool ok= Ans.size()==N;
	if (ok) {
		for (int i=0;i<Ans.size();++i) {
			printf("%d ", Ans[i]);
		}
		puts("");
	} else {
		puts("ERROR");
	}
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void Init() {
	fill(G[0], G[0]+MAXN*MAXN, false);
	fill(In,In+MAXN,0);	
}

int main(int argc, char** argv) {
	while (scanf("%d",&N) != EOF) {
		Init();
		for (int i=0;i<N;++i) {
			for (int j=0;j<N;++j) {
				int e;
				scanf("%d",&e);
				G[i][j]=e;
				In[j]+=e; // i->j
			}
		}
		TopoSort();
	}
	return 0;
}
