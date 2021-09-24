#include <algorithm>
#include <cstdio>
using namespace std;

/*
输入图的邻接矩阵，跑Floyd，输出距离矩阵。节点0--N-1。
*/

#define MAXN 55
int d[MAXN][MAXN];
int N;
const int INF = 1e9;

void Floyd() {
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j]) {
          d[i][j] = d[i][k] + d[k][j];
        }
      }
    }
  }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  while (scanf("%d", &N) != EOF) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        int w;
        scanf("%d", &w);
        // 注意，w=0有两种情况，一种i==j，另一种i!=j.
        if (i != j && w == 0) {
          w = INF;
        }
        d[i][j] = w;
      }
    }
    Floyd();
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        int ans = d[i][j];
        printf("%d ", ans == INF ? -1 : ans);
      }
      puts("");
    }
  }
  return 0;
}
