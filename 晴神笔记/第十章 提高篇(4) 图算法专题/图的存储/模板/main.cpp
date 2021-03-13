#include <cstdio>
#include <vector> // 一般用vector实现。 
using namespace std;
 
/*
图的存储：
1. 邻接矩阵，O(V^2)，适合节点数小于1000.
	边权放在矩阵的元素中。
	 
2. 邻接表，O(V+E)，适合节点数大于1000.
	边权放在链表元素中。 
*/

#define MAXN 100 // 节点数上限。

/*
如果i->j，即i有一条出边到j，则G[i][j]存放的是该边的边权，否则存放特殊值，比如无穷大。
对于无向图，如果有i->j，则必有j->i，所以无向图的矩阵是对称矩阵。 
*/
 
int G[MAXN][MAXN];

/*
加边操作：
修改对应的矩阵元素，比如要加边 i->j，边权为 w，则：
*/
void Add(int i, int j, int w) {
	G[i][j]=w;
} 

/*
Adj是vector数组，Adj的长度等于节点数，即每个节点i保存其所有的出边在Adj[i] 中。
如果仅保存出边的终点编号，则用int。否则定义一个结构体 Node，记录边的边权和终点编号。
*/
 
vector<int> Adj[MAXN];

// 一条边的信息。 
struct Node {
	int v; // 终点。
	int w; // 权重。
	// 构造器，方便加边。
	Node(int _v, int _w) {
		v=_v;
		w=_w;
	} 
};

vector<Node> Adj2[MAXN];

/*
加边操作：
比如，要加边 i->j，边权为w，则：
1. 无边权：
*/
void Add2(int i, int j) {
	Adj[i].push_back(j);
}
/*
2. 有边权：
*/
void Add3(int i, int j, int w) {
	Adj2[i].push_back(Node(j, w));
}
/*
3. 无向图加边 i<->j：（有边权同理） 
*/
void Add4(int i, int j) {
	Adj[i].push_back(j);
	Adj[j].push_back(i);
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	return 0;
}
