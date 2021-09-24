#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
/*
如果使用密集存储,则合并同类项和去除0,需要实现顺序表算法,
比较麻烦.虽然可以节省空间.

若使用稀疏存储,则合并同类项比较方便,并且0项可以直接跳过不输出.
代价是要开一个比较大的数组做指数的直接映射.
*/

// 指数为i的系数保存在a[i]中.
#define MAXN 1005
double a[MAXN];

int main(int argc, char *argv[]) {
  int k1, k2, k3; // 三个多项式的非零项.
  int i;

  // 输入第一个多项式.
  scanf("%d", &k1);
  for (i = 0; i < k1; ++i) {
    int e;
    double c;
    scanf("%d%lf", &e, &c);
    a[e] += c;
  }

  // 输入第二个多项式,并做加法.
  scanf("%d", &k2);
  for (i = 0; i < k2; ++i) {
    int e;
    double c;
    scanf("%d%lf", &e, &c);
    a[e] += c;
  }
  k3 = 0;
  for (i = 0; i < MAXN; ++i) {
    if (a[i])
      ++k3;
  }
  //注意,如果k3==0,则输出了k3后不能有空格.
  printf("%d", k3);
  for (i = MAXN - 1; i >= 0; --i) {
    if (a[i] != 0.0) {
      printf(" %d %.1f", i, a[i]);
    }
  }
  return 0;
}
