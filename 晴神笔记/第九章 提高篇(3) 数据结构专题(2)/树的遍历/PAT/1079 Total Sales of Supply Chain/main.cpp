#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define MAXN (100000+5)
struct Node {
	double price;
	int product;
	vector<int> child;
};

Node node[MAXN];

int N;
double P, r;
vector<int> leaves;
const int root=0;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
ÿ��ļ�Ǯ����һ��ĳ��������������нڵ�ļ�Ǯ��
*/ 
void BFS() {
	queue<int> Q;
	Q.push(root);
	node[root].price=P;
	double rate=1+r/100;
	
	while (!Q.empty()) {
		int now=Q.front();
		Q.pop();
		for (int i=0;i<node[now].child.size();++i) {
			int p=node[now].child[i];
			Q.push(p);
			node[p].price=node[now].price*rate;
		}
	}
}

int main(int argc, char** argv) {
	scanf("%d%lf%lf", &N, &P, &r);
	for (int i=0;i<N;++i) {
		int n;
		scanf("%d", &n);
		if (n) {
			while (n--) {
				int child;
				scanf("%d", &child);
				node[i].child.push_back(child);
			}
		} else {
			// n=0;
			scanf("%d", &node[i].product);
			leaves.push_back(i);
		}
	}
	BFS();
	double ans=0;
	// ��������Ҷ�ӣ����㼴�ɡ�
	for (int i=0;i<leaves.size();++i) {
		int p=leaves[i];
		ans += node[p].product * node[p].price;
	}
	printf("%.1f\n", ans);
	return 0;
}
