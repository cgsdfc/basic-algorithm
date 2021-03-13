#include <cstdio>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
 
/*
AOE，AOV 网求关键路径和关键活动。

AOE和AOV网是等价的，AOV可以通过分点法来转换为AOE。

AOE网其实就是一个有向无环图（DAG），没有点权，有非负的边权。
而关键路径就是AOE网的最长简单路径，使用了工程方面的术语来描述算法。

对于本算法，要注意以下：
1. ve，vl数组的计算，这是算法的主体。
2. 关键路径长度，关键活动（关键边），关键路径本身的获取，
这是算法的输出。

算法主体：
ve，vl数组的计算是有递推公式的，只要按照拓扑序列（或者逆序）的顺序来递推计算即可。
注意ve是间接更新，即公式是由前驱推出后继，实现是用前驱去更新后继，而不是遍历某节点的全部前驱。
vl是直接计算，即遍历某节点的全部后继，公式也是后继推出前驱。
ve的计算伴随着拓扑序列的生成，而vl的计算则逆序遍历已经生成的拓扑序列。

算法输出：
1. 关键活动，就是满足e==l的边，而e和l（即活动的最早开始时间和最晚开始时间）
是由边的两个端点u,v的ve和vl得出的，公式为：
设有边 u->v ，边权为w ，则：
e=ve[u]
l=vl[v]-w。
即边的最早开始时间等于前驱的最早开始时间，边的最晚开始时间等于后继的最晚开始时间减去边权。
满足此条件的即为关键活动（边）。

2. ve数组的最大值就是关键路径长度。回想ve的计算方式，其实是计算了一系列路径的长度，
即每个节点的ve，其实是源点到该节点的关键路径的长度，所以其实求出ve就知道了关键路径的长度。

3. 关键路径本身的获取：
在当前的边u->v为关键边时，把边保存到邻接表中，这样到最后，邻接表就保存了包含了所有关键路径
的图，这个图是一个DAG，假定它添加了超级源点S和超级汇点T，于是遍历所有S和T之间的路径（其实就是原
图所有源点到所有汇点的路径），就得到了全部关键路径。 

4. 关于源点和汇点。
1. 入度为零的点是源点，出度为零的点是汇点，为了方便计算，如果图的源点或者汇点不唯一，那么可以添加
超级源点S或者超级汇点T，S的出边连接所有原图源点，T的入边连接所有原图汇点。并且这些新加的边的边权为0。
最后注意S和T的入度要计算出来，并且输出路径时，不要输出它们。如果原图有唯一源点汇点（给出了或者发现了），
就记录下来，并且关键路径要输出它们。 
*/

#define MAXN 505 // 最大节点数。

/*
一条边，可以设置e，l，记录边的e，l数据。
*/ 
struct Node {
	int v; // 终点。 
	int w; // 边权。
	int e; // 活动最早开始时间。
	int l; // 活动最晚开始时间。 
};

vector<Node> Adj[MAXN];
vector<Node> Ans[MAXN]; // 保存全部关键路径。
int S,T; // 唯一源点，唯一汇点。
 
int ve[MAXN], vl[MAXN];
int In[MAXN];

/*
使用栈来保存拓扑序列的原因：
先要用到拓扑序列计算ve，这在入栈时获取；
出栈时可以获得逆拓扑序列，这在计算vl时要用到。
用栈可以方便获取逆拓扑序列，当然reverse也可以。
因为拓扑序列的逆序列就是逆拓扑序列。 
*/
 
stack<int> topOrder; // 拓扑序列。

// 求解拓扑序列，顺便求解ve数组，即节点事件的最早开始时间。 
bool TopoSort() {
	queue<int> Q;
	for (int i=0;i<N;++i) {
		// 入度为0的点入队。
		if (!In[i]) {
			Q.push(i);
		} 
	}
	/*
	拓扑排序，同时保证了访问一个节点时，它的前驱都被访问过了。
	计算ve的公式是：
	j的ve是其前驱的ve加上边权的和的最大值。
	但是我们的邻接表是保存后继的，对一个节点找它的前驱不方便。
	所以采取了等价的做法：访问到一个节点时，更新它的所有后继的ve值。
	为什么正确：访问当前节点时，它的前驱都被访问过了，这意味着它的所有前驱都更新了它，
	所以它的值是正确的，再用这正确的值去更新后继。
	注意，这个过程和计算vl不同，vl是需要访问u的全部后继来更新u，这是可以直接完成的。 
	
	最后，注意vl和ve的初始化即可。 
	*/
	fill(ve, ve+MAXN, 0);
	while (!Q.empty()) {
		int u=Q.front();
		Q.pop();
		topOrder.push(u);
		// 更新后继的ve。
		for (int i=0;i<Adj[u].size();++i) {
			int v=Adj[u][i].v;
			int w=Adj[u][i].w;
			--In[v];
			if (!In[v]) {
				Q.push(v);
			}
			if (ve[u]+w > ve[v]) {
				ve[v]=ve[u]+w;
			}
		} 
	}
	// 无环返回true，排序成功，有环返回false，排序失败，
	// 这说明题图不是DAG，不存在关键路径。这里的逻辑是：
	// 给定一个AOE（就是DAG），它的关键路径是最长简单路径，
	// 如果不是DAG，则不存在关键路径，因为关键路径的前提是AOE。 
	return N==topOrder.size();
}

/*
求解关键路径的主程序。
如果关键路径不存在，返回-1，否则返回关键路径长度。 
*/ 
int CriticalPath() {
	// 先求拓扑序列和ve数组。
	if (!TopoSort()) {
		return -1;
	}
	int maxLen=0; // 关键路径长度，等于ve数组的最大值。
	// 也等于唯一汇点的ve值。 
	for (int i=0;i<N;++i) {
		if (ve[i] > maxLen) {
			maxLen=ve[i];
		}
	}
	// 求解vl数组。 
	// vl数组的初始化，是maxLen。
	fill(vl, vl+MAXN, maxLen);
	// 逆拓扑序列，遍历后继取最小值。
	while (!topOrder.empty()) {
		int u=topOrder.top();
		topOrder.pop();
		// 所有后继。
		for (int i=0;i<Adj[u].size();++i) {
			int v=Adj[u][i].v; // 后继。
			int w=Adj[u][i].w;
			// 后继的vl减去边权，最小化。 
			if (vl[v]-w < vl[u]) {
				vl[u]=vl[v]-w;
			} 
		} 
	}
	// 有了ve 和vl，就遍历全部边，求每条边的e和l。
	for (int u=0;u<N;++u) {
		for (int i=0;i<Adj[u].size();++i) {
			int v=Adj[u][i].v;
			int w=Adj[u][i].w;
			// 边的最早等于前驱的最早。
			int e=ve[u];
			// 边的最晚等于后继的最晚减去边权。
			int l=vl[v]-w;
			Adj[u][i].e=e;
			Adj[u][i].l=l;
			if (e == l) {
				// 我是关键边。
				// 记录关键路径，整条边复制过去。 
				Ans[u].push_back(Adj[u][i]);
				printf("%d->%d\n", u,v);
			}
		}
	} 
	// 返回关键路径长度。
	return maxLen; 
}

/*
算法的输入，和拓扑排序类似，要记录节点的入度，
然后注意题目要求，如果只是输出关键路径长度，则运行第一部分（求解ve即可），
如果求关键活动，则运行至第三部分，求出e，l。如果要输出全部路径，就要
知道唯一源点和唯一汇点，这样DFS才比较方便。
*/
 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	return 0;
}
