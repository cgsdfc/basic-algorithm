#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
矩阵变换：
原矩阵的第i行，变为目标矩阵的第i列，并且元素逆序。
*/

#define MAXN 1005
int old[MAXN][MAXN], now[MAXN][MAXN];
int N, M;

void Rotate() {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      now[M - j - 1][i] = old[i][j];
    }
  }
}

int main(int argc, char **argv) {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf("%d", &old[i][j]);
    }
  }
  Rotate();
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      printf("%d%s", now[i][j], j == N - 1 ? "\n" : " ");
    }
  }
  return 0;
}
