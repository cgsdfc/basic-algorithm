#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N; // 苹果树数量。
int M; // 操作次数。

// 在线处理，不需要数组。

int T, K, P; // T剩余苹果总数，K苹果减少最多的苹果树，P为其减少的苹果数。

int main(int argc, char **argv) {
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= N; ++i) {
    int all;     // 当前总苹果数（操作前）。
    int tot = 0; // 减少苹果的总数。
    scanf("%d", &all);
    for (int j = 0; j < M; ++j) {
      int op;
      scanf("%d", &op); // 对当前苹果树进行操作。
      if (op < 0) {
        // 进行操作。
        all += op;
        tot -= op;
      }
    }
    T += all;
    if (tot > P) {
      P = tot;
      K = i;
    }
  }
  printf("%d %d %d\n", T, K, P);

  return 0;
}
