#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib> // atoi
#include <queue>
//#include <iostream>
//#include <iomanip>
#include <cmath>

using namespace std;

struct Node {
	int v;
	int dis;
	Node(int _v, int _d):v(_v),dis(_d) {
	}
	// �������á� 
	friend bool operator<(Node a, Node b) {
		return a.dis > b.dis;
	}
};

/*
�ֱ����M����վ��N�����ӵľ��루�������·���ĳ��ȣ���Ȼ�������Ŀ������������ɸѡ��
*/

/*
���ӵı��1--N����վ���N+1--N+1+M��
*/

#define MAXV (1000+10+5)

#define MAXN (1000+5) // ������
#define MAXM (10+5) // ��վ��

const int INF=1e9;

int d[MAXV]; // ĳ����վ�������ڵ�ľ��롣 
int N,M,K,Ds; // ����������վ��������������Χ��
bool vis[MAXV];
vector<Node> Adj[MAXV];

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct Gas {
	// ��վ���ݡ�
	int minDis;
	int aveDis; // ���Ϊ�������� 
	int id;
	Gas(int m, int a, int i):minDis(m),aveDis(a),id(i) {
	}
	friend bool operator<(Gas a, Gas b) {
		if (a.minDis != b.minDis) {
			return a.minDis > b.minDis;
		}
		if (a.aveDis != b.aveDis) {
			return a.aveDis < b.aveDis;
		}
		return a.id < b.id;
	}
};

vector<Gas> gas;

int change(char str[]) {
	if (str[0] == 'G') {
		return atoi(str+1)+N;
	}
	return atoi(str);
}

void Dijkstra(int s) {
	fill(vis, vis+MAXV, false);
	fill(d, d+MAXV, INF);
	d[s]=0;
	priority_queue<Node> Q;
	Q.push(Node(s, 0));
	while (!Q.empty()) {
		int u=Q.top().v;
		Q.pop();
		if (vis[u]) continue;
		vis[u]=true;
		for (int i=0;i<Adj[u].size();++i) {
			int v=Adj[u][i].v;
			int dis=Adj[u][i].dis;
			if (!vis[v] && d[u]+dis<d[v]) {
				d[v]=d[u]+dis;
				Q.push(Node(v, d[v]));
			}
		}
	}
}


int main(int argc, char** argv) {
	scanf("%d%d%d%d",&N,&M,&K,&Ds);
	while (K--) {
		char s1[10], s2[10];
		int d;
		scanf("%s%s%d", s1,s2,&d);
		int u=change(s1);
		int v=change(s2);
		Adj[u].push_back(Node(v, d));
		Adj[v].push_back(Node(u, d));
	}
	for (int i=1;i<=M;++i) {
		// ����ÿ����վ���������ӵľ��롣
		int s=i+N;
		Dijkstra(s);
		bool ok=true;
		Gas g(INF, 0, i);
//		printf("G%d\n", i);
		
		for (int j=1;j<=N;++j) {
			int dis=d[j];
//			printf("%d d %d\n", j, dis);
			
			if (dis > Ds) {
				ok=false;
				break;
			}
			if (dis < g.minDis) {
				g.minDis=dis;
			}
			g.aveDis += dis;
		}
		if (!ok) {
			continue; // һ���Ƿ���վ�� 
		}
		gas.push_back(g);
	}
	if (gas.empty()) {
		puts("No Solution");
	} else {
		sort(gas.begin(), gas.end());
		Gas g=gas[0];
		printf("G%d\n", g.id);
//		cout << setprecision(1)<<setiosflags(ios::fixed)<< (double)g.minDis
//		<< " " << setprecision(1) << setiosflags(ios::fixed) << (double)g.aveDis/N << "\n";
		double ans=(double)g.aveDis/N;
		// �ֶ��������뵽1λС���� 
		ans=round(ans*10)/10;
		
		printf("%.1f %.1f\n", (double)g.minDis, ans);
		
	}
	
	return 0;
}
