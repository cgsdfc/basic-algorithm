#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1000

int ans[MAXN];

/*
题目说的因子，不是指素因子，所以1也是一个因子，
而是指所有能整除N并且不等于N的数。
求N的所有因子和求所有素因子不同。

只要枚举1--N的整数即可。
可以优化到sqrtN，因为若P是因子，则N/P也是因子。
并且若P小于等于sqrtN，则N/P大于等于sqrtN，所以枚举1--sqrtN即可。

可见，分解因数问题可以不用到素数。
当然，一个数的所有因数的和，也可以用质因数的公式。但是没必要。
*/

int Judge(int N) {
  int sum = 0;
  int sqr;
  int i;

  // 1不是完数。
  if (N == 1)
    return 0;
  sqr = sqrt(N);

  //	printf("sqr %d\n", sqr);

  for (i = 1; i <= sqr; ++i) {
    if (N % i == 0) {
      int p = N / i;
      sum += i;
      if (p != N && p != i) {
        sum += p;
      }
    }
  }
  return sum == N;
}

int main(int argc, char *argv[]) {
  int N;

  while (scanf("%d", &N) != EOF) {
    int j;
    int num = 0; // 完数个数。

    //		printf("%d\n", N);

    for (j = 2; j <= N; ++j) {
      if (Judge(j)) {
        ans[num++] = j;
      }
    }
    //		printf("num %d\n", num);

    for (j = 0; j < num; ++j) {
      printf("%d%s", ans[j], j == num - 1 ? "\n" : " ");
    }
  }
  return 0;
}
