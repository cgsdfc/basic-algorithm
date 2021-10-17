#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>
using namespace std;

struct Edge {
    int u, v;
    double dis;
};

struct Point {
    double X, Y;
};

#define MAXN 105
int N;
Point point[MAXN];
bool vis[MAXN];
double d[MAXN];
const double INF = numeric_limits<double>::max();

// 平方距离。
double Dis(int a, int b) {
    double ans = pow(point[a].X - point[b].X, 2) + pow(point[a].Y - point[b].Y, 2);
    //	return sqrt(ans);
    return ans;
}

double Prim(int s) {
    fill(vis, vis + MAXN, false);
    fill(d, d + MAXN, INF);
    d[s] = 0;
    double ans = 0;
    for (int i = 0; i < N; ++i) {
        int u = -1;
        double MIN = INF;
        for (int j = 0; j < N; ++j) {
            if (!vis[j] && d[j] < MIN) {
                MIN = d[j];
                u = j;
            }
        }
        //		printf("u %d d %.3lf\n", u, d[u]);
        // 完全图，不存在不连通的问题。
        vis[u] = true;
        ans += sqrt(d[u]);
        //		ans += d[u];
        for (int j = 0; j < N; ++j) {
            double dis;
            if (!vis[j] && (dis = Dis(u, j)) < d[j]) { d[j] = dis; }
        }
    }
    return ans;
}

/*
节点是二维坐标，图是完全图，边是两个节点的欧氏距离。
求最小生成树和边权和。是稠密图，但是朴素的prim和kruskal的复杂度
接近。
*/

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
注：此题在codeup无法通过，精度问题。样例的精度都不对。
*/

int main(int argc, char** argv) {
    while (scanf("%d", &N), N) {
        for (int i = 0; i < N; ++i) {
            scanf("%lf%lf", &point[i].X, &point[i].Y);
        }
        double ans = Prim(0);
        printf("%.2f\n", ans);
    }
    return 0;
}
