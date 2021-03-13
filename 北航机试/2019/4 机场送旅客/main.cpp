#include <cstdio>
#include <vector>
#include <algorithm>
#include <map> // �ڵ�ת�±ꡣ 
using namespace std;

#define MAXN 505 // �ڵ����ޡ�
// N�����ݡ� 
int N;
vector<int> Adj[MAXN]; 
bool vis[MAXN];
vector<int> Path;

#define MAXM 105
int M;

int index; // ����ڵ��±ꡣ
map<int,int> mp; // ����ת�±ꡣ 
int mp2[MAXN]; // �±�ת���֡� 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
�Ӹ�����������A����A�������ﵽB���Դ����ƣ��ﵽ���һ���ÿͺ�
���ظ���������M���ÿͣ����M+1�У�ÿ����һ��·��
ע�⣬ÿ��·�����˵�һ���⣬��Ҫ�����㣬����ÿ��·��Ҫ����յ㡣 
����������¼Ϊ����ͼ��DFS��ÿ��·��

ÿ��DFS�ĸ��Ӷ��Ǳ���ȫͼ��������M+1�Σ����Ӷ�ΪO(M*(E+V))�� 
*/
// �Ƿ��ӡԴ�㣬���˵�һ��·�⣬������ӡԴ�㡣 
int start=0;

void DFS(int s, int t) {
	if (s == t) {
		Path.push_back(s);
		// ���·����
		// ע��˳���ӡ�� 
		for (int i=start;i<Path.size();++i) {
			int v=Path[i];
			int ans=mp2[v];
			printf("%d%s", ans,i==Path.size()-1?"\n":" ");
		}
		Path.pop_back();
		return;
	}
	vis[s]=true;
	Path.push_back(s);
	for (int i=0;i<Adj[s].size();++i) {
		int v=Adj[s][i];
		if (!vis[v]) {
			DFS(v, t);
		}
	}
	Path.pop_back();
	vis[s]=false;
}

void PrintPath(int s, int t) {
	fill(vis,vis+MAXN,false);
	Path.clear();
	DFS(s, t);
	if (!start) {
		start=1;
	}
}


int Map(int x) {
	if (mp.count(x)) {
		return mp[x];
	} else {
		mp[x]=index;
		mp2[index]=x;
		return index++;
	}
}

struct Person {
	int v; // Ŀ�ĵأ�Ҷ�ӽڵ㡣
	int prio; // ���ȼ��� 
	friend bool operator<(Person a, Person b) {
		return a.prio < b.prio;
	}
} P[MAXM]; // �ÿ� 

// ��¼������ 
int Root;

int main(int argc, char** argv) {
	scanf("%d",&N);
	for (int i=0;i<N;++i) {
		// ��ͼ��
		int u; // ���ڵ㡣
		scanf("%d",&u);
		u=Map(u);
		if (!i) {
			// ��֤��һ�е�һ���ڵ��Ǹ��� 
			Root=u;
		}
		int T=3;
		while (T--) {
			// �������ӡ�
			int v;
			scanf("%d",&v);
			if (v == -1) {
				continue;
			}
			v=Map(v);
			Adj[u].push_back(v);
			Adj[v].push_back(u);
		} 
	}
	scanf("%d", &M);
	for (int i=0;i<M;++i) {
		int v;
		scanf("%d%d",  &v,&P[i].prio);
		P[i].v=Map(v);
	}
	sort(P, P+M);
	for (int i=0;i<M;++i) {
		int u, v;
		if (i==0) {
			u=Root;
			v=P[i].v;
		} else {
			u=P[i-1].v;
			v=P[i].v;
		}
		PrintPath(u, v);
	}
	// �ص����� 
	PrintPath(P[M-1].v, Root);
	
	return 0;
}
