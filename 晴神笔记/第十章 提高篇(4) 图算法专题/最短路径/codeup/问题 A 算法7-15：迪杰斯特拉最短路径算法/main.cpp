#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 55
const int INF=1e9;

int N, S; // 节点数，源点。
int G[MAXN][MAXN];
bool vis[MAXN];
int d[MAXN];

/*
直接求出最短路长度，然后按照节点从大到小的顺序输出，源点的距离不输出。
注意存在不可达的节点。 
*/

void Dijkstra(int s) {
	fill(vis, vis+N, false);
	fill(d, d+N, INF);
	d[s]=0;
	for (int i=0;i<N;++i) {
		// N轮，每轮解决一个节点。
		int v=-1;
		int MIN=INF;
		// 找最小。
		for (int u=0;u<N;++u) {
			if (!vis[u] && d[u] < MIN) {
				v=u;
				MIN=d[u];
			}
		}
		if (v==-1) {
			return; // 剩下的不可达。 
		}
		vis[v]=true;
		// 扫描v的邻居进行松弛，用邻接矩阵和邻接表这里不同。
		for (int u=0;u<N;++u) {
			if (!vis[u] && G[v][u] != INF && d[v]+G[v][u] < d[u]) {
				d[u]=d[v]+G[v][u];
			}
		} 
	}
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	while (scanf("%d%d", &N, &S) != EOF) {
		for (int i=0;i<N;++i) {
			for (int j=0;j<N;++j) {
				int w;
				scanf("%d", &w);
				if (!w && i!=j) {
					// 没有边。
					w=INF; 
				}
				G[i][j]=w;
			}
		}
		Dijkstra(S);
		int k=0;
		for (int i=0;i<N;++i) {
			if (i == S) continue;
			int ans=d[i]==INF?-1:d[i];
			printf("%d%s", ans, k==N-2?"\n":" ");
			++k;
		}
	}
	return 0;
}
