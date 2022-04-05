#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100
// int parent[MAXN];
// bool leaf[MAXN]; // true 表示是叶子节点。

const int root = 1;

int N;  // 节点数。

// void Init() {
//	fill(parent, parent+MAXN, -1);
//	fill(leaf, leaf+MAXN, true);
//}

/*
这种求树高的方法时间复杂度是n平方。
不可取，用BFS，或者代码短的DFS，
时间都是n，空间的话，不用考虑。
codeup的数据较弱，n平方算法不会超时，
它的优点是省内存，编码复杂度更低。
*/

// int TreeHeight() {
//	int ans=0; // 空树的高。
//	for (int i=1;i<=N;++i) {
//		if (leaf[i]) {
//			int hi=1;
//			int p=i;
//			while (p != root) {
//				p=parent[p];
//				++hi;
//			}
//			if (hi > ans) {
//				ans=hi;
//			}
////			printf("%d hi %d\n", i, hi);
//		}
//	}
//	return ans;
//}

// 因为没有数据域，直接这样。这是多叉树的孩子列表，也是图的邻接表。
vector<int> node[MAXN];

/*
DFS 可以求树高度，
1. 空树，H=0
2. 非空树，H=max{Hi,...}+1，Hi是子树高度。

当题目要求根的高度是0或者1时，可根据题意给DFS的返回值减一。
*/

int DFS(int root) {
    if (node[root].empty()) {
        // 叶节点。边界。
        return 1;
    }
    int ans = -1;
    for (int i = 0; i < node[root].size(); ++i) {
        int h = DFS(node[root][i]);
        ans = max(ans, h);
    }
    return ans + 1;
}

int main(int argc, char** argv) {
    //	Init();
    scanf("%d", &N);
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) {
        // b是a的子节点。
        //		parent[b]=a;
        //		leaf[a]=false;
        node[a].push_back(b);
    }
    //	int ans=TreeHeight();
    int ans = DFS(root);
    printf("%d\n", ans);

    return 0;
}
