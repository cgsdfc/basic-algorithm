#include <cstdio>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
ע�⵽��������ĿҪ���γɵ��߶Σ���ʵ��ɭ�֣��ڵ���ƽ�����꣬���������ֱ�߶Ρ�
���ҵ������������������Ϊ0�Ľڵ㣬Ȼ����������ߣ�������ߺ������� 

�����Ĺؼ��ǣ���ĿҪ������ӷ�ʽ��������ô���ģ�
�ǲ�����ͬ�Ķ˵�������ӣ�
����ֻ����˵������Ҷ˵㣿

����ע�⣺����涨ֻ����˵������Ҷ˵㣬��ô��Ȼ�γ�ɭ�֣�����ÿ���߶��������Ȼ���Ǽ�·����
��������������Ϊ�����������ô�ֲ�ĵط�����Ȼ����˵�������˵㣬�����������ǲ����ڵġ�
���Ծ�����Щ�߶ΰ�����˵������Ҷ˵��γ����������Ƕ���ÿһ�������壨Ҳ���Ƕ��������߶����ĵ�λ����
ֻ�ܿ��ǴӸ���Ҷ�ӵ�·�������۾��ǣ���һ��ɭ��������ĸ���Ҷ�ӵ�·���� 

��������ӵ�Ҫ����ɵ�ֻҪ��ͬһ������Զ����ӣ��Ǿ���������ͼ�������ͨ�����Լ���Ա����

ע�⣺������������������DAG����Ȼһ���ж����̣���ôҲ�Ϳ����ж��ǰ����
�ⲻΥ������β�����������Ƕ���һ�����߶���˵������·������������ͱ����DAG�·��
����ö��Դ�㵽��������·���������·�����ȡ� 
*/

// ��N���߶Σ����� 2*N ���ڵ㡣 
const int MAXN = (1e4+5);
const int MAXP = (2*MAXN);

typedef pair<int,int> Point;
map<Point, int> mp;
Point mp2[MAXP];

int index;
int N;
vector<int> Adj[MAXP];
int In[MAXP]; // �ڵ����ȡ�

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

// ���Դ������������·������󳤶ȡ� 
void DFS(int s, int len, int& maxLen) {
	if (Adj[s].empty()) {
		// s�ǻ�㣬����Ϊ0.
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
		// ����һ���߶ε������˵㡣 
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
		// ������Դ�㵽���л���·���� 
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
