#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, M;
const int K = 3;

#define MAXN 35

bool rm[MAXN][MAXN]; // true ��ʾ��ɾ����
int a[MAXN][MAXN];   // ���̡�

void Solve() {
  // ö��������������Ԫ�ء�
  for (int i = 0; i < N; ++i) {
    int j = 0;
    while (j < M) {
      int k = j;
      while (k < M && a[i][k] == a[i][j]) {
        ++k;
      }
      int len = k - j;
      if (len >= K) {
        while (j != k) {
          rm[i][j] = true;
          ++j;
        }
      } else {
        j = k;
      }
    }
  }
  // ö��������������Ԫ�ء�
  for (int j = 0; j < M; ++j) {
    int i = 0;
    while (i < N) {
      int k = i;
      while (k < N && a[k][j] == a[i][j]) {
        ++k;
      }
      int len = k - i;
      if (len >= K) {
        while (i != k) {
          rm[i][j] = true;
          ++i;
        }
      } else {
        i = k;
      }
    }
  }
}

int main(int argc, char **argv) {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  Solve();
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      int x = rm[i][j] ? 0 : a[i][j];
      printf("%d%s", x, j == M - 1 ? "\n" : " ");
    }
  }
  return 0;
}
