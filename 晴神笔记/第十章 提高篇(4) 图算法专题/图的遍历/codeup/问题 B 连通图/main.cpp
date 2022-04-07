#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, M;

/*
如果不能在一次BFS完成所有节点的访问，则图不是联通的。
用bfs判断图的连通性。
*/

#define MAXN 1005

bool inq[MAXN];
vector<int> Adj[MAXN];

int BFS(int s) {
    int ans = 0;  // 本次访问的节点总数。
    queue<int> Q;
    Q.push(s);
    inq[s] = true;
    while (!Q.empty()) {
        // bfs访问的结点都要经过这里。
        ++ans;
        int v = Q.front();
        Q.pop();
        for (int i = 0; i < Adj[v].size(); ++i) {
            int u = Adj[v][i];
            if (!inq[u]) {
                inq[u] = true;
                Q.push(u);
            }
        }
    }
    return ans;
}

bool Judge() {
    // 或者可以看一次bfs能否把inq全部置为true。
    fill(inq, inq + N + 1, false);
    int n = BFS(1);
    return n == N;
}

int main(int argc, char** argv) {
    while (scanf("%d", &N), N) {
        scanf("%d", &M);

        while (M--) {
            int x, y;
            scanf("%d%d", &x, &y);
            // 无向图。
            Adj[x].push_back(y);
            Adj[y].push_back(x);
        }
        bool ans = Judge();
        puts(ans ? "YES" : "NO");
        for (int i = 1; i <= N; ++i) {
            Adj[i].clear();
        }
    }

    return 0;
}
