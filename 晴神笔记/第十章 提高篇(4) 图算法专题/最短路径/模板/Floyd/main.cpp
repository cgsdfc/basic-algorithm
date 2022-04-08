#include <algorithm>
#include <cstdio>
using namespace std;

int N, M;  // 点数，边数。

/*
Floyd（弗洛伊德）算法，计算全源最短路，就是所有节点对i，j之间的最短路径。
复杂度O(N^3)。本质上是DP算法。
*/

#define MAXN 205  // 适用弗洛伊德算法的节点数，不多于200.

const int INF = 1e9;

// 距离数组（矩阵），因为是全源最短路，所以从单源最短路的数组变为矩阵，
// d[u][v] 表示从u到v的最短路长度。而d[v][u]表示从v到u的最短路长度。
// 对于无向图，d是对称矩阵。
int d[MAXN][MAXN];

// 能处理有向图，当然也能处理无向图。
void Floyd() {
    // 节点从0--N-1，三重循环，最外层枚举中间节点k，
    // 里面两层循环枚举节点对i，j。当i，j之间通过节点k能使路径更短时，
    // 更新距离数组d。从形式上看，三重循环的变量分别是k，i，j，都是从0到N-1.
    // 循环体的松弛逻辑是关键，注意三个变量的位置。
    for (int k = 0; k < N; ++k) {
        // k从小到大枚举，体现了动态规划思想。
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                // d数组即为G，输入进行初始化。
                if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j]) {
                    // 如果i可达k，且k可达j，且路径i-->k-->j的长度小于路径i-->j，就松弛。
                    // 本质上，i和j，如果中间绕路到k，反而使得路径变短，就松弛。
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    scanf("%d%d", &N, &M);
    /*
    d矩阵的初始化：
    i到j的距离，如果存在边i->j，则d[i][j]为边权。
    否则就是INF。如果没有自环，则d[i][i]=0，一般都没有自环。

    注意：这个版本的Floyd，图使用邻接矩阵表示（因为方便），而距离矩阵使用和邻接矩阵相同的矩阵，
    并且算法在图上原地进行。即没有矩阵G，只有矩阵d，d先接受输入并初始化，然后算法对d进行修改，最后输出d。
    */
    // 注意：二维矩阵的初始化方法。
    fill(d[0], d[0] + MAXN * MAXN, INF);
    for (int i = 0; i < N; ++i) {
        d[i][i] = 0; // 自己到自己的距离为0
    }
    // 注意d的初始化包含了输入的部分，所以必须和主程序的输入部分结合，而不要放到Floyd子程序里面。
    while (M--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        d[u][v] = w;  // 有向图。若是无向图则加上 d[v][u]=w;
    }
    Floyd();
    // 输出题目要求的节点对之间的最短距离，一般以查询的形式给出，
    // 这样用弗洛伊德就变成了预计算与O(1)查询，这样会使复杂度与查询数无关。
    // 如果在线计算则复杂度与查询数有关。
    int K;
    scanf("%d", &K);
    while (K--) {
        int u, v;
        scanf("%d%d", &u, &v);
        int ans = d[u][v];
        printf("%d\n", ans);
    }

    return 0;
}
