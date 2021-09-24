#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N; // 苹果树数量。

#define MAXN 1005

bool drop[MAXN];
int T; // 剩下的总数。
int D; // 发生脱离的苹果树个数。
int E; // 连续发生脱离的组数。

int main(int argc, char **argv) {
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) {
    int m;
    scanf("%d", &m);
    int all;           // 当前苹果总数。
    scanf("%d", &all); // 第一个操作一定是统计个数。
    m--;
    while (m--) {
      int op;
      scanf("%d", &op);
      if (op > 0) {
        // 统计苹果个数。
        if (all > op) {
          // 发生了脱落。
          drop[i] = true;
        }
        all = op;
      } else {
        all += op;
      }
    }
    T += all;
    if (drop[i]) {
      //			printf("%d\n", i);
      ++D;
    }
  }
  for (int i = 1; i <= N; ++i) {
    // 检查每一颗树的左边，右边，自己是否脱落。
    int left = i == 1 ? N : i - 1;
    int right = i == N ? 1 : i + 1;
    if (drop[left] && drop[right] && drop[i]) {
      //			printf("%d %d %d\n", left, i, right);
      ++E;
    }
  }
  printf("%d %d %d\n", T, D, E);

  return 0;
}
