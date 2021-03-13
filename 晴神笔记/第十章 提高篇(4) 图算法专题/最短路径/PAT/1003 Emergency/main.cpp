#include <cstdio>
#include <algorithm>
#include <set> // Bellman ͳ��·��������
#include <vector> // Bellman �ڽӱ� 
#include <queue> // SPFA�ǻ��ڶ��е��Ż��� 
using namespace std;

const int INF=1e9;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
�����·���������Լ����е����·���棬���ĵ�Ȩ�͡�
�ڶ����Ϊ��Ȩ�͵����⡣
*/

int N, M; // ������������
int S, T; // Դ�㣬�յ㡣

#define MAXN 505 // �ڵ����� 

int G[MAXN][MAXN]; // �����Ȩ�����룩 
int d[MAXN]; 
bool vis[MAXN];

int weight[MAXN]; // �����Ȩ�� 
int w[MAXN];
int num[MAXN]; // ·��������
 
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
				// ����d��С��δ���ʵĽڵ㡣
				u=j;
				MIN=d[j]; 
			}
		}
		if (u==-1) {
			return; // ���ų���Щ�ڵ㲻�ɴ 
		}
		vis[u]=true;
		// ���²�����
		for (int j=0;j<N;++j) {
			if (!vis[j] && G[u][j] != INF) {
				// δ���ʲ��ҿɴ
				if (d[u]+G[u][j] < d[j]) {
					d[j]=d[u]+G[u][j];
					num[j]=num[u];
					w[j]=w[u]+weight[j];
				} else if (d[u]+G[u][j] == d[j]) {
					num[j] += num[u];
					if (w[u]+weight[j] > w[j]) {
						w[j]=w[u]+weight[j]; // ���µڶ���ߡ� 
					}
				}
			}
		} 
	}
}

/*
��bellmanʵ�ֱ��⡣
1. �ڶ���ߵ�ʵ�ֺ�Dijkstra���ơ�
2. ·������ͳ�ƱȽϲ�ͬ����Ҫset�� 
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
// bellman��Ҫ�ڽӱ������Ӷ�ΪO(V^3)����E�ڼ�������²���O(V^2)�� 
// ���һ�������E=logV�����Ӷ�ΪO(ElogV)�� 

// ��֤·�����ڡ� 
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
				// �ɳڡ� 
				int v=Adj[u][i].v;
				int dis=Adj[u][i].dis;
				if (d[u]+dis < d[v]) {
					// ����������ߡ� 
					d[v]=d[u]+dis;
					w[v]=w[u]+weight[v];
					// ·�������¡� 
					num[v]=num[u];
					pre[v].clear();
					pre[v].insert(u);
				} else if (d[u]+dis == d[v]) {
					if (w[u]+weight[v] > w[v]) {
						w[v]=w[u]+weight[v];
					}
					// ·�������¡� 
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
��SPFAʵ�ֱ��⡣
ע�Ȿ���num��·��������SPFA��num����Ӵ�����
��Ҫ�������飬inq��num��d������num�ǿ�ѡ�ġ� 
*/
//int Num[MAXN]; // ���������֤�н⣬�ʲ���Ҫ�жϡ� 
bool inq[MAXN]; // �Ƿ���ӡ�

void SPFA(int s) {
	fill(d, d+N, INF);
	fill(inq, inq+N, false);
	fill(w, w+N, 0);
	fill(num, num+N, 0);
	
	queue<int> Q; // �ǽڵ��ŵĶ��С�
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
						BUG�㣺 
						�ڶ���߸��ŵ�·�����Ƿ���Ҫ��չ��
						������ڶ�����һ�����ͬ��·������ôҪȡ�����еڶ�������ġ�
						����ͨ���ڵ�u��·����������v�ĵڶ���߱仯������v��Ҫ����ӡ�
						*/ 
						inq[v]=true;
						Q.push(v);
					}
				}
			}
		}
	} 
}

// �����·�������� 
void DFS(int s, int v, int& ans) {
	if (s == v) {
		// ����Դ�㣬�õ�һ��·���� 
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
		// Ӧ��������ͼ�� 
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
