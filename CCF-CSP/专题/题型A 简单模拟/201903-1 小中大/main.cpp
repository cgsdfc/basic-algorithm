#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N;
int Min, Max, Mid;

int main(int argc, char **argv) {
  /*
  最小值，最大值都是整数，
  偶数的中位数是两个中间数的平均值，可能是浮点数。
  */
  scanf("%d", &N);
  bool odd = N & 1;

  /*
  注意，数据可能为升序或者降序！！。
  */
  for (int i = 0; i < N; ++i) {
    int x;
    scanf("%d", &x);
    // 第一个必是最小值。
    if (i == 0) {
      Min = x;
    }
    if (i == N - 1) {
      Max = x;
    }
    if (odd && i == N / 2) {
      Mid = x;
    }
    if (!odd && (i == N / 2 || i == N / 2 - 1)) {
      Mid += x;
    }
  }
  // 关键。
  if (Max < Min) {
    swap(Max, Min);
  }

  printf("%d ", Max);
  if (odd) {
    printf("%d", Mid);
  } else {
    if (Mid % 2 == 0) {
      // 中位数是整数。
      printf("%d", Mid / 2);
    } else {
      printf("%.1f", (double)Mid / 2);
    }
  }
  printf(" %d\n", Min);
  return 0;
}
