#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, M;
#define MAXN 505
int In[MAXN];
vector<int> Adj[MAXN];

void TopoSort() {
    priority_queue<int, vector<int>, greater<int>> Q;
    for (int v = 1; v <= N; ++v) {
        if (!In[v]) { Q.push(v); }
    }
    int i = 0;
    while (!Q.empty()) {
        int u = Q.top();
        Q.pop();
        printf("%d%s", u, i == N - 1 ? "\n" : " ");
        ++i;
        for (int j = 0; j < Adj[u].size(); ++j) {
            int v = Adj[u][j];
            --In[v];
            if (!In[v]) { Q.push(v); }
        }
    }
}

int main(int argc, char** argv) {
    while (scanf("%d%d", &N, &M), (N || M)) {
        fill(In, In + MAXN, 0);
        fill(Adj, Adj + MAXN, vector<int>());

        while (M--) {
            int u, v;
            scanf("%d%d", &u, &v);  // u->v
            Adj[u].push_back(v);
            In[v]++;
        }
        TopoSort();
    }
    return 0;
}
