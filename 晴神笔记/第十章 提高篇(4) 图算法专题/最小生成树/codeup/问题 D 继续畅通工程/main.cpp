#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 105

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 如果两点已经建成公路，则cost=0。 
int G[MAXN][MAXN];
const int INF=1e9;
bool vis[MAXN];
int d[MAXN];
int N;

struct Node {
	int v,dis;
	Node(int vv, int dd):v(vv),dis(dd){
	}
	friend bool operator<(Node a, Node b) {
		return a.dis > b.dis;
	}
};

int Prim(int s) {
	fill(d,d+MAXN,INF);
	fill(vis,vis+MAXN,false);
	d[s]=0;
	priority_queue<Node> Q;
	Q.push(Node(s, 0));
	int ans=0;
	while (!Q.empty()) {
		int u=Q.top().v;
		Q.pop();
		if (vis[u]) continue;
		vis[u]=true;
		ans+=d[u];
		for (int v=1;v<=N;++v) {
			if (!vis[v] && G[u][v] != INF && G[u][v] < d[v]) {
				d[v]=G[u][v];
				Q.push(Node(v, d[v]));
			}
		}
	}
	return ans;
}

int main(int argc, char** argv) {
	while (scanf("%d",&N), N) {
		int M=N*(N-1)/2;
		fill(G[0], G[0]+MAXN*MAXN, INF);
		while (M--) {
			int u,v,cost,ok;
			scanf("%d%d%d%d",&u,&v,&cost,&ok);
			if (ok) {
				cost=0;
			}
			G[u][v]=G[v][u]=cost;
		}
		int ans=Prim(1);
		printf("%d\n", ans);
	}
	return 0;
}
