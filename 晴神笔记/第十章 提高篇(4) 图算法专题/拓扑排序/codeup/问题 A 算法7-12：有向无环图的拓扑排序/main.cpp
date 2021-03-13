#include <cstdio>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

/*
��Stackģ�����������㷨����������Queue��Stack��һ��������Ϊ�㷨��ʵֻ��Ҫһ���ṹ��ʱ�������Ϊ0�Ľڵ�
��������ʹ������ⷴ��ɨ��ȫ���ڵ㣩�� 
��ͬ���ǲ���û��ƫ���ϵ��Ԫ�ص�˳���ȷ����
*/

#define MAXN 55
bool G[MAXN][MAXN];
int In[MAXN]; // ��ȡ�
int N;

void TopoSort() {
	stack<int> S;
	vector<int> Ans; // ��������С� 
	// �ڵ�0--N-1.
	for (int v=0;v<N;++v) {
		if (!In[v]) {
			S.push(v);
		}
	}
	while (!S.empty()) {
		int u=S.top();
		S.pop();
		Ans.push_back(u);
		for (int v=0;v<N;++v) {
			if (G[u][v]) { // u->v
				--In[v];
				if (!In[v]) {
					S.push(v);
				}
			}
		}
	}
	bool ok= Ans.size()==N;
	if (ok) {
		for (int i=0;i<Ans.size();++i) {
			printf("%d ", Ans[i]);
		}
		puts("");
	} else {
		puts("ERROR");
	}
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void Init() {
	fill(G[0], G[0]+MAXN*MAXN, false);
	fill(In,In+MAXN,0);	
}

int main(int argc, char** argv) {
	while (scanf("%d",&N) != EOF) {
		Init();
		for (int i=0;i<N;++i) {
			for (int j=0;j<N;++j) {
				int e;
				scanf("%d",&e);
				G[i][j]=e;
				In[j]+=e; // i->j
			}
		}
		TopoSort();
	}
	return 0;
}
