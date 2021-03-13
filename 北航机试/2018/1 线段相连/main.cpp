#include <cstdio>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
注意到：按照题目要求形成的线段，其实是森林，节点是平面坐标，边是两点的直线段。
先找到所有树根，就是入度为0的节点，然后求最大树高，输出树高和树根。 

这道题的关键是，题目要求的连接方式究竟是怎么样的？
是不是相同的端点就能连接？
还是只能左端点连接右端点？

另外注意：如果规定只能左端点连接右端点，那么必然形成森林，并且每条线段联合体必然都是简单路径，
而不能是树，因为如果是树，那么分叉的地方，必然有左端点连接左端点，而这种连接是不存在的。
所以就算这些线段按照左端点连接右端点形成了树，但是对于每一个联合体（也就是独立计算线段数的单位），
只能考虑从根到叶子的路径。推论就是：在一个森林里求最长的根到叶子的路径。 

如果把连接的要求放松到只要是同一个点就自动连接，那就是在有向图里计算连通分量以及成员数。

注意：不是树！不是树！是DAG，既然一点有多个后继，那么也就可以有多个前驱。
这不违反“首尾相连”，但是对于一条大线段来说，还是路径，所以问题就变成求DAG最长路。
可以枚举源点到汇点的所有路径，求最大路径长度。 
*/

// 有N条线段，即有 2*N 个节点。 
const int MAXN = (1e4+5);
const int MAXP = (2*MAXN);

typedef pair<int,int> Point;
map<Point, int> mp;
Point mp2[MAXP];

int index;
int N;
vector<int> Adj[MAXP];
int In[MAXP]; // 节点的入度。

int Map(Point p) {
	if (mp.count(p)) {
		return mp[p];
	} else {
		mp[p]=index;
		mp2[index]=p;
		return index++;
	}
}

Point Read() {
	Point p;
	scanf("%d%d",&p.first,&p.second);
	return p; 
}

// 求从源点出发到达汇点的路径的最大长度。 
void DFS(int s, int len, int& maxLen) {
	if (Adj[s].empty()) {
		// s是汇点，出度为0.
		if (len > maxLen) {
			maxLen=len;
		}
		return;
	}
	for (int i=0;i<Adj[s].size();++i) {
		int v=Adj[s][i];
		DFS(v, len+1, maxLen);
	}
}

int main(int argc, char** argv) {
	scanf("%d",&N);
	while (N--) {
		// 输入一条线段的两个端点。 
		Point a=Read();
		Point b=Read();
		int u=Map(a);
		int v=Map(b);
		Adj[u].push_back(v);
		In[v]++;
	}
	
	int ans=0;
	int v;
	for (int i=0;i<index;++i) {
		// 求所有源点到所有汇点的路径。 
		if (!In[i]) {
			int s=i;
			int maxLen=0;
			DFS(s, 0, maxLen);
			if (maxLen > ans) {
				ans=maxLen;
				v=s;
			}
		}
	}
	printf("%d %d %d\n", ans, mp2[v].first, mp2[v].second);
	
	return 0;
}
