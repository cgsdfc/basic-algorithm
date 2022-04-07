#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
using namespace std;

const int INF = 1000000000;

#define MAXN (10000 + 5)
int N;
vector<int> Adj[MAXN];
bool vis[MAXN];
// 有最大距离的节点对的端点。
set<int> Ans;

void DFS(int u, int depth, int& hi) {
    vis[u] = true;
    if (depth > hi) { hi = depth; }
    for (int i = 0; i < Adj[u].size(); ++i) {
        int v = Adj[u][i];
        if (!vis[v]) { DFS(v, depth + 1, hi); }
    }
}

int TreeHi(int root) {
    // 计算root为根的树的高度。
    int ans = 0;
    fill(vis, vis + N + 1, false);
    DFS(root, 0, ans);
    return ans;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int father[MAXN];  // 并查集检查联通性。
void Init() {
    for (int i = 1; i <= N; ++i) {
        father[i] = i;
    }
}
int Find(int x) {
    int a = x;
    while (x != father[x]) {
        x = father[x];
    }
    while (a != father[a]) {
        int temp = father[a];
        father[a] = x;
        a = temp;
    }
    return x;
}
void Union(int a, int b) {
    int faA = Find(a);
    int faB = Find(b);

    if (faA != faB) { father[faA] = faB; }
}
void Print() {
    for (int i = 1; i <= N; ++i) {
        printf("%d: ", i);
        for (int j = 0; j < Adj[i].size(); ++j) {
            printf("%d ", Adj[i][j]);
        }
        printf("\n");
    }
}

// 联通分量数。
int FindComp() {
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        // 看看N个节点，那个是根。
        if (father[i] == i) { ++ans; }
    }
    assert(ans > 0);
    return ans;
}

/*
这个O(VE+V^2)的算法居然过了，说明PAT的测试数据比较弱。
*/

/*
有定理加持的高效算法：
1. 选择任意节点作为根，进行DFS，获取深度最大的节点集合，记为A。
2. 任取A的一个元素，以此为根，进行DFS，获深度最大的节点集合，记为B。
3. 所求的最深根节点集合记为 A 并 B。

复杂度：O(V+E)，即DFS的复杂度。
*/

/*
对某个节点进行DFS遍历，记录下最深的节点，记录在vi中。
一边求最大深度，一边统计深度最大的点，有技巧。
*/
void DFS2(int u, int depth, int& maxDepth, vector<int>& vi) {
    vis[u] = true;
    //	printf("u %d maxd %d\n", u, maxDepth);

    if (depth > maxDepth) {
        // 注意更新全局最大值。
        maxDepth = depth;
        vi.clear();
        vi.push_back(u);  // u的深度达到新高。
    } else if (depth == maxDepth) {
        // 达到当前最大深度。
        vi.push_back(u);
    }
    for (int i = 0; i < Adj[u].size(); ++i) {
        int v = Adj[u][i];
        if (!vis[v]) { DFS2(v, depth + 1, maxDepth, vi); }
    }
}

// 找某节点为根的最深叶节点集合。
// 即以某节点为根的树，深度为树高的叶节点集合。
void FindDeep(int root, vector<int>& vi) {
    int deep = 0;
    fill(vis, vis + N + 1, false);
    DFS2(root, 0, deep, vi);
}

/*
计算最深根（Deepest Roots）集合。
使用定理的版本。
*/
void Compute2() {
    vector<int> A, B;
    // 计算集合A，即某节点出发的最深节点集合。
    FindDeep(1, A);

    assert(A.size());
    // 计算集合B，即A的某元素出发的最深节点集合。
    FindDeep(A.front(), B);

    // 计算AB的并集。
    set<int> ans;
    vector<int>::iterator it;
    for (it = A.begin(); it != A.end(); ++it) {
        //		printf("%d\n", *it);
        ans.insert(*it);
    }
    //	puts("");
    for (it = B.begin(); it != B.end(); ++it) {
        //		printf("%d\n", *it);
        ans.insert(*it);
    }
    // ans 即为最深根节点集合，并且排序。
    for (set<int>::iterator it = ans.begin(); it != ans.end(); ++it) {
        printf("%d\n", *it);
    }
}

/*
暴力版本。
*/
void Compute() {
    int ans = -1;
    for (int v = 1; v <= N; ++v) {
        // 计算以v为根的树高。
        int hi = TreeHi(v);
        // 更新全局最大值。
        if (hi > ans) {
            ans = hi;
            Ans.clear();
            Ans.insert(v);
        } else if (hi == ans) {
            Ans.insert(v);
        }
    }

    set<int>::iterator it;
    // 从小到大输出。
    for (it = Ans.begin(); it != Ans.end(); ++it) {
        printf("%d\n", *it);
    }
}

int main(int argc, char** argv) {
    scanf("%d", &N);
    int M = N - 1;
    /*
    注意，树的一个条件，即E=V-1已经满足，只需要检查联通性是否满足。
    因为联通且E=V-1的必定是树，不用检查环了。
    */
    Init();  // 并查集初始化。
    while (M--) {
        int a, b;
        scanf("%d%d", &a, &b);
        Adj[a].push_back(b);
        Adj[b].push_back(a);
        // 无向图。
        Union(a, b);
    }
    // 用并查集可以快速检查连通性。
    int n = FindComp();
    if (n != 1) {
        // 不是联通图，不是树。
        printf("Error: %d components\n", n);
    } else {
        Compute2();
    }
    return 0;
}
