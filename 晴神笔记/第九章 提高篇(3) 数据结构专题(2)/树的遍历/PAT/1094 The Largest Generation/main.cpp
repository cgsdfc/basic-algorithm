#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/*
�ȱ궨ÿ���ڵ��level��
ͬʱ��ɢ��ͳ��ÿһ��level �Ľڵ�����
����������level�����ֵ���ɡ�
*/

#define MAXN 105

struct Node {
	int level; // ���ڵ��level=1.
	vector<int> child; 
} node[MAXN];

/*
����level�ǳ�Ϊһ����ʱ����ΪN-1.
*/
int level[MAXN];

int N; // �ܽڵ� 
int M; // ��Ҷ�ڵ� 
const int root=1;
int MaxLevel;

// �������level�� 
int BFS() {
	queue<int> Q;
	Q.push(root);
	node[root].level=1;
	int ans=-1;
	
	while (!Q.empty()) {
		int now=Q.front();
		Q.pop();
		// ͬһ��level��������һ�� 
		level[node[now].level]++;
		// ͬʱ������level�������ſ��Ա�������level�� 
		if (node[now].level > ans) {
			ans=node[now].level;
		}
		
		for (int i=0;i<node[now].child.size();++i) {
			int p=node[now].child[i];
			Q.push(p);
			node[p].level=node[now].level+1;
		}
	}
	return ans;
	
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	scanf("%d%d", &N, &M);
	for (int i=0;i<M;++i) {
		int p; // ���ڵ㡣
		int n; // ��������
		scanf("%d%d", &p, &n);
		while (n--) {
			int c; // ���ӡ�
			scanf("%d", &c);
			node[p].child.push_back(c); 
		} 
	}
	MaxLevel=BFS();
	int ans=0; // ���������
	int gen; // ��Ӧ�Ĵ���
	for (int i=1;i<=MaxLevel;++i) {
		if (level[i] > ans) {
			ans=level[i];
			gen=i;
		}
	} 
	printf("%d %d\n", ans, gen);
	
	return 0;
}
