#include <cstdio>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> Point;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 表示一个窗口。 
struct Node {
	Point up, down;
	int id;
	// 检查p是否落于窗口内。 
	bool In(Point& p) {
		return down.first<=p.first&&p.first<=up.first &&
		down.second<=p.second&&p.second<=up.second;
	}
};

vector<Node> node;

int N, M;

int Find(Point& p) {
	for (int i=node.size()-1;i>=0;--i) {
		// 最顶层窗口在最后面。
		if (node[i].In(p)) {
			return i;
		} 
	}
	return -1;
}

int main(int argc, char** argv) {
	scanf("%d%d", &N, &M);
	for (int i=1;i<=N;++i) {
		Node p;
		p.id=i;
		scanf("%d%d%d%d", &p.down.first, &p.down.second, &p.up.first, &p.up.second);
		node.push_back(p);
	}
	while (M--) {
		Point p;
		scanf("%d%d", &p.first, &p.second);
		int pos=Find(p);
		if (pos == -1) {
			puts("IGNORED");
		} else {
			printf("%d\n", node[pos].id);
			Node x=node[pos];
			node.erase(node.begin()+pos);
			node.push_back(x);
		}
	}
	return 0;
}
