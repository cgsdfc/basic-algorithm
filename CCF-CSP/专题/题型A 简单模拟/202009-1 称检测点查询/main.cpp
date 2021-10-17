#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 205

int id[MAXN];

struct Point {
    int X, Y;
};

Point p[MAXN];

Point now;  // 当前位置。

int N;

// a 到 now 的距离
int Dis(Point& a) {
    int dx = a.X - now.X;
    int dy = a.Y - now.Y;
    return dx * dx + dy * dy;
}

bool cmp(int a, int b) {
    // 距离小的在前面。
    int da = Dis(p[a]);
    int db = Dis(p[b]);
    if (da != db) { return da < db; }
    // 下标小的在前面。
    return a < b;
}

/*
N<=200，数据量非常小，排序然后取前三个即可。
*/

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    scanf("%d%d%d", &N, &now.X, &now.Y);
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &p[i].X, &p[i].Y);
        id[i] = i;
    }
    sort(id + 1, id + N + 1, cmp);
    for (int i = 1; i <= 3; ++i) {
        printf("%d\n", id[i]);
    }
    return 0;
}
