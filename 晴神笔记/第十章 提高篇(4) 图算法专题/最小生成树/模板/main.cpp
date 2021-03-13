#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/*
��С�������������㷨��
1. Prim������ķ�㷨��VlogV���ʺϳ���ͼ�� 
2. Kruskal����³˹�����㷨��ElogE���ʺ�ϡ��ͼ��
�����·�������У����·�����ܲ��������Ƶ��ǣ���С������Ҳ���ܲ����ڡ�
�����ڵ�������ͼ������ͨͼ�������������Ȳ����ڡ�����������㷨�ж���С�������Ƿ���ڵ��߼�
ֵ�ù�ע��Prim��ͨ����Dijkstra���Ƶģ�ĳһ���Ҳ����ڵ�u���㵽S�ľ��벻��INF��˵��ʣ�µĽڵ�ȫ��
��S�����ڣ�����ض���ǰ���ֱ����¾��룬Ȼ�����ڵľ���Ͳ���INF�ˣ�����ʱ�ж�ͼ����ͨ��
Kruskal���ò��鼯�ж����ϲ��Ĵ��������������ı�������ͨͼǡ�úϲ�N-1�Σ�����ͨ��ͼ�ĺϲ���������N-1��
����Ϊ�˴˲���ͨ�ķ���֮���޷��ϲ����� 
*/

/*
Prim �㷨����Dijkstra�Ŀ����һ���ģ�ά���������ϣ�
S��V-S��ÿ�δ�V-S��ѡȡ��S���ϵĽڵ�ľ�����С�Ľڵ㣬����S�У�
��������ڵ����V-Sʣ�µĽڵ����С���롣ͨ��ά��d���飬��ĳ�ڵ㵽S���ϵ���С���룬
������ѡ��ڵ�u��ʱ���ۼ� d[u]���õ���С�ı�Ȩ�͡�

��Ҫ�����ݽṹ��Dijkstra��һ���ģ���������d�����������ɳڲ����������;�������� 
ͼ�����ݽṹ�������ڽӱ�����ڽӾ��� 

�㷨�Ĺ�����̣�
1. ѭ��N�Σ�ÿ��ѡ��һ���ڵ㣬ͬʱ������������һ���߼��뵽��С���������ۼƱ�Ȩ�͡�
2. ÿ��ѡ��ڵ�ı�׼�����뵱ǰ��S���ϵľ�����С�Ľڵ㡣�������һ����ĳ���ߵı�Ȩ��
�����Ǳ�Ȩ�ļӺ͡�����S���һ�㣬�뼯��S�ڵ����ɽڵ���ֱ�������ıߣ����б�Ȩ��С�߾���
����˵�ľ��롣����뼯��S�ڵĽڵ�û��ֱ�������ıߣ���ô����������INF��

��˵���㷨����ȷ�ԣ�
ά��S�����ڵĽڵ㣬����ѡ��ı������ɵ�ͼ���ǰ�����Щ�ڵ����ͼ����С��������
��Ҫ��һ���ڵ㼴������һ���߼���S����ʱ������ѡ����S�Ľڵ�ֱ���������ұ�Ȩ��С���Ǹ��ڵ㡣
����ѡ����ֱ�������Ľڵ㣬��ôҪ��֤S�Ľڵ��������ͼ������һ���ıߺͽڵ㣬����S�Ľṹ�Ͳ���ͨ�ˡ�
���������ӽṹ���������ȼ����𲽼���ֱ�������Ľڵ㡣
����ѡ��Ľڵ�ı�Ȩ������С�ģ���ô���Υ����S�����ʡ�

Prim���Զ��Ż��� 
*/

#define MAXN 505 // �ڵ����ޡ�

int G[MAXN][MAXN]; // Prim�ʺϵ���ͼ�������ڽӾ����ǲ����ʵġ�
 
// �ڽӱ��Ԫ�أ��յ�ͱ�Ȩ�� 
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
int pre[MAXN]; // ��¼MST����ͨ�����ױ�ʾ���� 
const int INF=1e9;

int N, M; // �ڵ�����������
 
/*
s��ѡ������������ΪS���ϵĳ�ʼ�ڵ㡣
�����Ƿ������С������������С��Ȩ�͡�ͬʱ��¼MST���� 
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
		// N��ѭ����ÿ������һ���ڵ㣬һ���ߣ����ı�ȨΪ0����
		// ����d��С��u��
		int u=-1;
		int MIN=INF;
		for (int j=0;j<N;++j) {
			if (!vis[j] && d[j] < MIN) {
				u=j;
				MIN=d[j];
			}
		}
		if (u == -1) {
			// ����ͨ��MST�����ڡ� 
			/*
			ע�⣬Dijkstra������߼���������ǰ�˳����������ж����·�����ڡ�
			��ʵ�ϣ�Dijkstra���趨�£����·���Ǵ��ڵģ���Ϊ�����踺�������ڡ�
			*/
			return false; 
		}
		vis[u]=true; // ���뼯��S��
		ans += d[u]; // �ۼƱ�Ȩ��
		// �ɳڲ�����
		for (int j=0;j<Adj[u].size();++j) {
			int v=Adj[u][j].v;
			int dis=Adj[u][j].dis;
			if (!vis[v] && dis < d[v]) {
				d[v]=dis; // d�����Ԫ���Ǳ�Ȩ�� 
				pre[v]=u; // ��Ϊ��S�����δѡ�нڵ㽫��ѡ��
				// ����ʹv��S�ľ�������u��Ϊv�ĸ��ڵ㡣 
			}
		} 
	}
	return true;
}

/*
���Ż���Prim��
*/
bool Prim2(int s, int& ans) {
	fill(vis,vis+MAXN,false);
	fill(d,d+MAXN,INF);
	d[s]=0; // ע����� 
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
		// ע�⣬d[u]������ΪINF����Ϊ���ɴ�Ľڵ㲻������ӡ� 
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
			// �ڵ㲻�ɴ
			return false; 
		}
	}
	return true;
}

/*
���ڲ��鼯��Kruskal����³˹�������㷨��
����ע�⵽�����鼯���������ж�ͼ����ͨ�ԡ�����ͼ�����бߣ�
��ÿ���ߵ������˵�����ָ��Union���������������ϸ��������ǡ��һ�����ϣ�
��ͼ����ͨ�ġ�ʵ���ϣ�������鼯������·��ѹ����������father����ǡ����ͼ����������
��Ϊ���鼯��������������ԭͼ�ıߣ����Ұ�����ͼ��ȫ���ڵ㡣

���ڣ�Ϊ��������С��������ֻ�а�̰�ĵ�˼��Ͳ��鼯��ϼ��ɡ����ǰ��ձ�Ȩ��С����Ŀ���
���еıߣ����кϲ��������������˵������������ʱ��˵���õ�����������һ���ߣ���Ϊ��������ά����ͨ����ģ�
���ұ�Ȩ����С�ģ������������߲�������������

�ж��Ƿ����MST���������Ǳ���ԭͼ��ͨ�Ե���С����E���Ƿ�����E=N-1������ȫ���߽���Union�����󣬵ó���E�Ǳ���ԭͼ
��ͨ�Ե���С�ı������������E=N-1����˵��ԭͼ��ͨ������Ͳ���ͨ��

�㷨�����ݽṹ�Ǳ��������бߵ�����Ͳ��鼯������Ҫ�ڽӱ�����ڽӾ���
�㷨�޷�ѡ����ڵ㣬��Ϊ�����ǵ���ȫ���ߡ����߱Ƚ��٣���Ƚ϶�ʱ����ϡ��ͼ���ʺϱ��㷨�� 
*/

struct Edge {
	int u,v,dis;
	Edge(int uu, int vv, int dd):u(uu),v(vv),dis(dd){
	}
	friend bool operator<(Edge a, Edge b) {
		return a.dis < b.dis; // ���� 
	}
};

#define MAXM 105

Edge edge[MAXM];
int father[MAXN]; // ���鼯��

// ���鼯�Ҹ��� 
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
	// ��ʼ�����鼯��
	for (int i=0;i<N;++i) {
		father[i]=i;
	}
	int num=0; // ��ǰ��MST������
	// ������̰�Ĳ��ԡ�
	sort(edge, edge+M);
	for (int i=0;i<M;++i) {
		int faU=Find(edge[i].u);
		int faV=Find(edge[i].v);
		if (faU != faV) {
			// �ϲ������Ҽ����±ߡ�
			++num;
			ans += edge[i].dis;
			if (num == N-1) {
				// �Ѿ��õ����ˡ��㷨��ǰ�˳���
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
