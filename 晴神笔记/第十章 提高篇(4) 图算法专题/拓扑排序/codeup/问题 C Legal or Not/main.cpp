#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;

/*
有向图判环。两种方法：
1. 拓扑排序判环。
2. DFS判环。本质上也是拓扑排序。
*/

int N, M;
#define MAXN 105

bool G[MAXN][MAXN];
int In[MAXN];

bool TopoSort() {
    queue<int> Q;
    for (int v = 0; v < N; ++v) {
        if (!In[v]) { Q.push(v); }
    }
    int num = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        ++num;
        for (int v = 0; v < N; ++v) {
            if (G[u][v]) {
                --In[v];
                if (!In[v]) { Q.push(v); }
            }
        }
    }
    return N == num;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    while (scanf("%d%d", &N, &M), N) {
        fill(G[0], G[0] + MAXN * MAXN, false);
        fill(In, In + MAXN, 0);
        while (M--) {
            int a, b;
            scanf("%d%d", &a, &b);  // 输入一条边 a->b
            /*
            注意，邻接矩阵对重边的处理导致出错。
            事实上邻接矩阵是不支持重边的，因为G[a][b]只有一个元素，并且遍历a的邻居时，
            对全部节点每个只考虑一次（相当于把重边给去重了，只保留了一条边），
            因此题目输入的重边没有表现在邻接矩阵中，但是会表现在In数组里，这样图和入度就不一致了，就出错了。

            用邻接表就没有这个问题，因为对于重边，u->v，则u的链表里会保留多份v的副本，访问u的邻居时，
            v被访问多次，会使v的入度相应的减少多次，因此图和入度一致，没有问题。

            如果仍要使用邻接矩阵，就必须在输入时检测重边，并对入度进行处理。本题来说，重边保留一条即可，所以
            入度数组也要去重。好在邻接矩阵可以快速查询某边是否存在，这样处理入度也很快。

            codeup有些题目有重边，必须考虑邻接表和邻接矩阵的区别然后正确处理。
            */
            if (!G[a][b]) {
                // 对于边ab，只添加一次。
                G[a][b] = true;
                ++In[b];
            }
        }
        bool ans = TopoSort();
        puts(ans ? "YES" : "NO");
    }

    return 0;
}
