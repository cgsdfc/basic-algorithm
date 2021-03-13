#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/*
最小生成树的两个算法：
1. Prim，普莱姆算法，VlogV，适合稠密图。 
2. Kruskal，克鲁斯卡尔算法，ElogE，适合稀疏图。
和最短路径问题中，最短路径可能不存在类似的是，最小生成树也可能不存在。
不存在的条件是图不是联通图，则生成树首先不存在。因此这两个算法判断最小生成树是否存在的逻辑
值得关注。Prim是通过和Dijkstra类似的，某一轮找不到节点u满足到S的距离不是INF，说明剩下的节点全部
和S不相邻（否则必定在前几轮被更新距离，然后现在的距离就不是INF了），此时判定图不联通。
Kruskal利用并查集判定，合并的次数等于生成树的边数，连通图恰好合并N-1次，不连通的图的合并次数少于N-1，
（因为彼此不连通的分量之间无法合并）。 
*/

/*
Prim 算法，和Dijkstra的框架是一样的，维护两个集合：
S，V-S。每次从V-S中选取到S集合的节点的距离最小的节点，加入S中，
并用这个节点更新V-S剩下的节点的最小距离。通过维护d数组，即某节点到S集合的最小距离，
并且在选择节点u的时候，累计 d[u]，得到最小的边权和。

需要的数据结构和Dijkstra是一样的，区别在于d数组的意义和松弛操作的条件和具体操作。 
图的数据结构可以是邻接表或者邻接矩阵。 

算法的构造过程：
1. 循环N次，每次选择一个节点，同时把与它相连的一条边加入到最小生成树，累计边权和。
2. 每次选择节点的标准，是与当前的S集合的距离最小的节点。这个距离一定是某条边的边权，
而不是边权的加和。集合S外的一点，与集合S内的若干节点有直接相连的边，其中边权最小者就是
这里说的距离。如果与集合S内的节点没有直接相连的边，那么这个距离就是INF。

简单说明算法的正确性：
维护S集合内的节点，及被选择的边所构成的图，是包含这些节点的子图的最小生成树。
当要把一个节点即相连的一条边加入S集合时，必须选择与S的节点直接相连并且边权最小的那个节点。
设想选择不是直接相连的节点，那么要保证S的节点是树，就加入多于一条的边和节点，否则S的结构就不连通了。
由于最优子结构，这样做等价于逐步加入直接相连的节点。
设想选择的节点的边权不是最小的，那么这就违反了S的性质。

Prim可以堆优化。 
*/

#define MAXN 505 // 节点上限。

int G[MAXN][MAXN]; // Prim适合点多的图，所以邻接矩阵是不合适的。
 
// 邻接表的元素，终点和边权。 
struct Node {
	int v, dis;
	Node(int vv, int dd):v(vv),dis(dd){
	}
	friend bool operator<(Node a, Node b) {
		return a.dis > b.dis;
	}
};

vector<Node> Adj[MAXN];
bool vis[MAXN];
int d[MAXN];
int pre[MAXN]; // 记录MST本身，通过父亲表示法。 
const int INF=1e9;

int N, M; // 节点数，边数。
 
/*
s：选定的树根，作为S集合的初始节点。
返回是否存在最小生成树，和最小边权和。同时记录MST本身。 
*/ 
bool Prim(int s, int& ans) {
	fill(vis,vis+MAXN, false);
	fill(d,d+MAXN,INF);
	d[s]=0;
	ans=0;
	for (int i=0;i<N;++i) {
		pre[i]=i;
	}
	for (int i=0;i<N;++i) {
		// N轮循环，每次增加一个节点，一条边（根的边权为0）。
		// 查找d最小的u。
		int u=-1;
		int MIN=INF;
		for (int j=0;j<N;++j) {
			if (!vis[j] && d[j] < MIN) {
				u=j;
				MIN=d[j];
			}
		}
		if (u == -1) {
			// 不连通。MST不存在。 
			/*
			注意，Dijkstra这里的逻辑作用是提前退出，而不是判定最短路不存在。
			事实上，Dijkstra的设定下，最短路总是存在的，因为它假设负环不存在。
			*/
			return false; 
		}
		vis[u]=true; // 加入集合S。
		ans += d[u]; // 累计边权。
		// 松弛操作。
		for (int j=0;j<Adj[u].size();++j) {
			int v=Adj[u][j].v;
			int dis=Adj[u][j].dis;
			if (!vis[v] && dis < d[v]) {
				d[v]=dis; // d数组的元素是边权。 
				pre[v]=u; // 因为离S最近的未选中节点将被选择，
				// 所以使v到S的距离变近的u作为v的父节点。 
			}
		} 
	}
	return true;
}

/*
堆优化的Prim。
*/
bool Prim2(int s, int& ans) {
	fill(vis,vis+MAXN,false);
	fill(d,d+MAXN,INF);
	d[s]=0; // 注意这里。 
	ans=0;
	priority_queue<Node> Q;
	Q.push(Node(s, 0));
	for (int i=0;i<N;++i) {
		pre[i]=i;
	}
	while (!Q.empty()) {
		int u=Q.top().v;
		Q.pop();
		if (vis[u]) continue;
		// 注意，d[u]不可能为INF，因为不可达的节点不可能入队。 
		vis[u]=true;
		ans += d[u];
		for (int i=0;i<Adj[u].size();++i) {
			int v=Adj[u][i].v;
			int dis=Adj[u][i].dis;
			if (!vis[v] && dis < d[v]) {
				d[v]=dis;
				pre[v]=u;
				Q.push(Node(v, d[v]));
			}
		}
	}
	for (int i=0;i<N;++i) {
		if (d[i] == INF) {
			// 节点不可达。
			return false; 
		}
	}
	return true;
}

/*
基于并查集的Kruskal（克鲁斯卡尔）算法。
首先注意到，并查集可以用来判断图的联通性。给定图的所有边，
对每条边的两个端点依次指向Union操作，最后计数集合个数，如果恰好一个集合，
则图是联通的。实际上，如果并查集不进行路径压缩，则最后的father数组恰好是图的生成树，
因为并查集本身是树，边是原图的边，并且包含了图的全部节点。

现在，为了生成最小生成树，只有把贪心的思想和并查集结合即可。就是按照边权从小到大的考虑
所有的边，进行合并操作，当两个端点分属两个集合时，说明得到了生成树的一条边（因为这条边是维持联通必须的，
并且边权是最小的），否则这条边不属于生成树。

判断是否存在MST的条件，是保持原图联通性的最小边数E，是否满足E=N-1，即对全部边进行Union操作后，得出的E是保持原图
联通性的最小的边数，如果满足E=N-1，则说明原图联通，否则就不连通。

算法的数据结构是保存了所有边的数组和并查集，不需要邻接表或者邻接矩阵。
算法无法选择根节点，因为它考虑的是全部边。当边比较少，点比较多时，即稀疏图，适合本算法。 
*/

struct Edge {
	int u,v,dis;
	Edge(int uu, int vv, int dd):u(uu),v(vv),dis(dd){
	}
	friend bool operator<(Edge a, Edge b) {
		return a.dis < b.dis; // 排序。 
	}
};

#define MAXM 105

Edge edge[MAXM];
int father[MAXN]; // 并查集。

// 并查集找根。 
int Find(int x) {
	int a=x;
	while (x != father[x]) {
		x=father[x];
	}
	while (a != father[a]) {
		int temp=father[a];
		father[a]=x;
		a=temp;
	}
	return x;
}

bool Kruskal(int& ans) {
	ans=0;
	// 初始化并查集。
	for (int i=0;i<N;++i) {
		father[i]=i;
	}
	int num=0; // 当前的MST边数。
	// 边排序，贪心策略。
	sort(edge, edge+M);
	for (int i=0;i<M;++i) {
		int faU=Find(edge[i].u);
		int faV=Find(edge[i].v);
		if (faU != faV) {
			// 合并，并且加入新边。
			++num;
			ans += edge[i].dis;
			if (num == N-1) {
				// 已经得到树了。算法提前退出。
				return true; 
			} 
		}
	}
	return num == N-1;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	return 0;
}
