#include <cstdio>
#include <algorithm>
#include <set> // Bellman 统计路径数量。
#include <vector> // Bellman 邻接表。 
#include <queue> // SPFA是基于队列的优化。 
using namespace std;

const int INF=1e9;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
求最短路的条数，以及所有的最短路里面，最大的点权和。
第二标尺为点权和的问题。
*/

int N, M; // 点数，边数。
int S, T; // 源点，终点。

#define MAXN 505 // 节点数。 

int G[MAXN][MAXN]; // 输入边权（距离） 
int d[MAXN]; 
bool vis[MAXN];

int weight[MAXN]; // 输入点权。 
int w[MAXN];
int num[MAXN]; // 路径数量。
 
void Dijkstra(int s) {
	fill(d, d+N, INF);
	fill(w, w+N, 0);
	fill(vis, vis+N, false);
	fill(num, num+N, 0);
	
	d[s]=0;
	w[s]=weight[s];
	num[s]=1;
	
	for (int i=0;i<N;++i) {
		int u=-1;
		int MIN=INF;
		for (int j=0;j<N;++j) {
			if (!vis[j] && d[j]<MIN) {
				// 查找d最小且未访问的节点。
				u=j;
				MIN=d[j]; 
			}
		}
		if (u==-1) {
			return; // 不排除有些节点不可达。 
		}
		vis[u]=true;
		// 更新操作。
		for (int j=0;j<N;++j) {
			if (!vis[j] && G[u][j] != INF) {
				// 未访问并且可达。
				if (d[u]+G[u][j] < d[j]) {
					d[j]=d[u]+G[u][j];
					num[j]=num[u];
					w[j]=w[u]+weight[j];
				} else if (d[u]+G[u][j] == d[j]) {
					num[j] += num[u];
					if (w[u]+weight[j] > w[j]) {
						w[j]=w[u]+weight[j]; // 更新第二标尺。 
					}
				}
			}
		} 
	}
}

/*
用bellman实现本题。
1. 第二标尺的实现和Dijkstra类似。
2. 路径数的统计比较不同，需要set。 
*/

set<int> pre[MAXN];
struct Node {
	int v;
	int dis;
	Node(int _v, int _dis) {
		v=_v;
		dis=_dis;
	}
};
vector<Node> Adj[MAXN];
// bellman需要邻接表，否则复杂度为O(V^3)，而E在极端情况下才是O(V^2)。 
// 如果一般情况下E=logV，则复杂度为O(ElogV)。 

// 保证路径存在。 
void Bellman(int s) {
	fill(d, d+N, INF);
	fill(w, w+N, 0);
	fill(num, num+N, 0);
	d[s]=0;
	num[s]=1;
	w[s]=weight[s];
	
	int T=N-1;
	while (T--) {
//		printf("%d\n", T);
		
		for (int u=0;u<N;++u) {
			for (int i=0;i<Adj[u].size();++i) {
				// 松弛。 
				int v=Adj[u][i].v;
				int dis=Adj[u][i].dis;
				if (d[u]+dis < d[v]) {
					// 更新两个标尺。 
					d[v]=d[u]+dis;
					w[v]=w[u]+weight[v];
					// 路径数更新。 
					num[v]=num[u];
					pre[v].clear();
					pre[v].insert(u);
				} else if (d[u]+dis == d[v]) {
					if (w[u]+weight[v] > w[v]) {
						w[v]=w[u]+weight[v];
					}
					// 路径数更新。 
					pre[v].insert(u);
					num[v]=0;
					for (set<int>::iterator it=pre[v].begin();it!=pre[v].end();++it) {
						num[v]+=num[*it];
					}
				}
			}
		}
	}
}

/*
用SPFA实现本题。
注意本题的num是路径数量，SPFA的num是入队次数。
需要三个数组，inq，num，d，其中num是可选的。 
*/
//int Num[MAXN]; // 入队数。保证有解，故不需要判断。 
bool inq[MAXN]; // 是否入队。

void SPFA(int s) {
	fill(d, d+N, INF);
	fill(inq, inq+N, false);
	fill(w, w+N, 0);
	fill(num, num+N, 0);
	
	queue<int> Q; // 是节点编号的队列。
	d[s]=0;
	inq[s]=true;
	w[s]=weight[s];
	Q.push(s);
	while (!Q.empty()) {
		int u=Q.front();
		Q.pop();
		inq[u]=false;
		for (int j=0;j<Adj[u].size();++j) {
			int v=Adj[u][j].v;
			int dis=Adj[u][j].dis;
			
			if (d[u]+dis < d[v]) {
				d[v]=d[u]+dis;
				w[v]=w[u]+weight[v];
				pre[v].clear();
				pre[v].insert(u);
				if (!inq[v]) {
					inq[v]=true;
					Q.push(v);
				}
			} else if (d[u]+dis == d[v]) {
				pre[v].insert(u);
				if (w[u]+weight[v] > w[v]) {
					w[v]=w[u]+weight[v];
					if (!inq[v]) {
						/*
						BUG点： 
						第二标尺更优的路径，是否需要扩展？
						如果存在多条第一标尺相同的路径，那么要取它们中第二标尺最大的。
						现在通过节点u的路径，能引起v的第二标尺变化，所以v需要被入队。
						*/ 
						inq[v]=true;
						Q.push(v);
					}
				}
			}
		}
	} 
}

// 求最短路径数量。 
void DFS(int s, int v, int& ans) {
	if (s == v) {
		// 到达源点，得到一条路径。 
		++ans;
		return;
	}
	set<int>::iterator it;
	for (it=pre[v].begin();it!=pre[v].end();++it) {
		DFS(s, *it, ans);
	}
}

int main(int argc, char** argv) {
	scanf("%d%d%d%d", &N,&M,&S,&T);
//	fill(G[0], G[0]+MAXN*MAXN, INF);
	for (int i=0;i<N;++i) {
		scanf("%d", &weight[i]);
	}
	while (M--) {
		// 应该是无向图。 
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
//		G[u][v]=G[v][u]=d;
		Adj[u].push_back(Node(v, d));
		Adj[v].push_back(Node(u, d));
	}
	
//	Dijkstra(S);
//	Bellman(S);
	SPFA(S);
	int ans=0;
	DFS(S, T, ans);
	printf("%d %d\n", ans, w[T]);
	
	return 0;
}
