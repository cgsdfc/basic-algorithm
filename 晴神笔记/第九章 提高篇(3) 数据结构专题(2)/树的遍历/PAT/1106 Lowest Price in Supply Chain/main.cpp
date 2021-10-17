#include <cassert>
#include <cmath>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
找深度最小的叶子节点的深度。
因为BFS的过程中，深度是逐渐增大的，所以找到第一个叶子节点
就可以退出了。

但是题目要求深度为最小的叶子的数量，这就要求出所有节点的深度了，
所以不能提前退出。

*/
#define MAXN (100000 + 5)

struct Node {
    int deep;
    vector<int> child;
} node[MAXN];

const int root = 0;
int N;
double P, r;

int BFS() {
    queue<int> Q;
    Q.push(root);
    node[root].deep = 0;
    bool flag = true;
    int ans = 0;

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        if (flag && node[now].child.empty()) {
            // 第一个叶节点出现了，即为最小深度。
            ans = node[now].deep;
            flag = false;
        }
        for (int i = 0; i < node[now].child.size(); ++i) {
            int p = node[now].child[i];
            node[p].deep = node[now].deep + 1;
            Q.push(p);
        }
    }
    return ans;
}

int main(int argc, char** argv) {
    scanf("%d%lf%lf", &N, &P, &r);
    for (int i = 0; i < N; ++i) {
        int n;  // 子节点数。
        scanf("%d", &n);
        while (n--) {
            int c;  // 孩子。
            scanf("%d", &c);
            node[i].child.push_back(c);
        }
    }
    // 输入完成。
    int ans = BFS();
    double rate = P * pow(1 + r / 100, ans);
    int num = 0;
    /*
    对于最大深度来说，可以直接在全部节点里面数，因为能达到最大深度的节点，
    必定是叶节点。但是对于最小深度来说，必须在叶节点里数，不然会混进非叶节点。
    */
    for (int i = 0; i < N; ++i) {
        if (node[i].child.empty() && node[i].deep == ans) { ++num; }
    }

    printf("%.4f %d\n", rate, num);

    return 0;
}
