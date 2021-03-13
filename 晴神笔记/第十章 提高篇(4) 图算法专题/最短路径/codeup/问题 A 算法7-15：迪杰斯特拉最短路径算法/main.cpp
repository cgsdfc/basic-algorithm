#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 55
const int INF=1e9;

int N, S; // �ڵ�����Դ�㡣
int G[MAXN][MAXN];
bool vis[MAXN];
int d[MAXN];

/*
ֱ��������·���ȣ�Ȼ���սڵ�Ӵ�С��˳�������Դ��ľ��벻�����
ע����ڲ��ɴ�Ľڵ㡣 
*/

void Dijkstra(int s) {
	fill(vis, vis+N, false);
	fill(d, d+N, INF);
	d[s]=0;
	for (int i=0;i<N;++i) {
		// N�֣�ÿ�ֽ��һ���ڵ㡣
		int v=-1;
		int MIN=INF;
		// ����С��
		for (int u=0;u<N;++u) {
			if (!vis[u] && d[u] < MIN) {
				v=u;
				MIN=d[u];
			}
		}
		if (v==-1) {
			return; // ʣ�µĲ��ɴ 
		}
		vis[v]=true;
		// ɨ��v���ھӽ����ɳڣ����ڽӾ�����ڽӱ����ﲻͬ��
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
					// û�бߡ�
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
