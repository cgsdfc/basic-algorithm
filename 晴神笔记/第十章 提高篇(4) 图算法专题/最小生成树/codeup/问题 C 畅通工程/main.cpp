#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, M;  // 边，点。

#define MAXN 105

struct Edge {
    int u, v, dis;
    friend bool operator<(Edge a, Edge b) {
        return a.dis < b.dis;
    }
};

Edge E[MAXN];
int father[MAXN];

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

bool Kruskal(int& ans) {
    ans = 0;
    sort(E, E + N);
    int num = 0;  // 边数。

    for (int i = 0; i < N; ++i) {
        int faU = Find(E[i].u);
        int faV = Find(E[i].v);
        if (faV != faU) {
            father[faV] = faU;
            ans += E[i].dis;
            ++num;
            if (num == M - 1) { return true; }
        }
    }
    return num == M - 1;
}

int main(int argc, char** argv) {
    while (scanf("%d%d", &N, &M), N) {
        // N边，M点。
        for (int i = 0; i < N; ++i) {
            Edge e;
            scanf("%d%d%d", &e.u, &e.v, &e.dis);
            E[i] = e;
        }
        // 并查集初始化。
        for (int i = 1; i <= M; ++i) {
            father[i] = i;
        }
        int ans = 0;
        if (Kruskal(ans)) {
            printf("%d\n", ans);
        } else {
            puts("?");
        }
    }
    return 0;
}
