#include <cstdio>
#include <vector>
#include <algorithm>
#include <map> // 节点转下标。 
using namespace std;

#define MAXN 505 // 节点上限。
// N行数据。 
int N;
vector<int> Adj[MAXN]; 
bool vis[MAXN];
vector<int> Path;

#define MAXM 105
int M;

int index; // 分配节点下标。
map<int,int> mp; // 数字转下标。 
int mp2[MAXN]; // 下标转数字。 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
从根出发，到达A，从A出发，达到B，以此类推，达到最后一个旅客后，
返回根，于是有M个旅客，输出M+1行，每行是一段路。
注意，每段路，除了第一段外，不要输出起点，但是每段路都要输出终点。 
把三叉树记录为无向图，DFS找每段路。

每次DFS的复杂度是遍历全图，共遍历M+1次，复杂度为O(M*(E+V))。 
*/
// 是否打印源点，除了第一段路外，都不打印源点。 
int start=0;

void DFS(int s, int t) {
	if (s == t) {
		Path.push_back(s);
		// 输出路径。
		// 注意顺序打印。 
		for (int i=start;i<Path.size();++i) {
			int v=Path[i];
			int ans=mp2[v];
			printf("%d%s", ans,i==Path.size()-1?"\n":" ");
		}
		Path.pop_back();
		return;
	}
	vis[s]=true;
	Path.push_back(s);
	for (int i=0;i<Adj[s].size();++i) {
		int v=Adj[s][i];
		if (!vis[v]) {
			DFS(v, t);
		}
	}
	Path.pop_back();
	vis[s]=false;
}

void PrintPath(int s, int t) {
	fill(vis,vis+MAXN,false);
	Path.clear();
	DFS(s, t);
	if (!start) {
		start=1;
	}
}


int Map(int x) {
	if (mp.count(x)) {
		return mp[x];
	} else {
		mp[x]=index;
		mp2[index]=x;
		return index++;
	}
}

struct Person {
	int v; // 目的地，叶子节点。
	int prio; // 优先级。 
	friend bool operator<(Person a, Person b) {
		return a.prio < b.prio;
	}
} P[MAXM]; // 旅客 

// 记录树根。 
int Root;

int main(int argc, char** argv) {
	scanf("%d",&N);
	for (int i=0;i<N;++i) {
		// 建图。
		int u; // 父节点。
		scanf("%d",&u);
		u=Map(u);
		if (!i) {
			// 保证第一行第一个节点是根。 
			Root=u;
		}
		int T=3;
		while (T--) {
			// 三个孩子。
			int v;
			scanf("%d",&v);
			if (v == -1) {
				continue;
			}
			v=Map(v);
			Adj[u].push_back(v);
			Adj[v].push_back(u);
		} 
	}
	scanf("%d", &M);
	for (int i=0;i<M;++i) {
		int v;
		scanf("%d%d",  &v,&P[i].prio);
		P[i].v=Map(v);
	}
	sort(P, P+M);
	for (int i=0;i<M;++i) {
		int u, v;
		if (i==0) {
			u=Root;
			v=P[i].v;
		} else {
			u=P[i-1].v;
			v=P[i].v;
		}
		PrintPath(u, v);
	}
	// 回到根。 
	PrintPath(P[M-1].v, Root);
	
	return 0;
}
