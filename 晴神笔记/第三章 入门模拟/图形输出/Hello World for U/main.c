#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 85

/*
将一个字符串以U型（二维矩阵）的形式输出，对矩阵的行数合列数有约束：
记 行数 为n，列数为m，行数即垂直臂长，列数即水平臂长。满足：
1. N=2*n+m-2，N是字符串的长度，即总字符数。
2. n<=m，且n尽量大。

由此可推导出n，m和N的关系式（根据不等式和取最大值的原理）：
1. n=floor( N+2) / 3 )
2. m=N+2-n*2

得出n和m后，再按要求打印。采用直接输出的办法，分清楚每行输出什么，再每一行，
分清楚每列输出什么。并且考虑到在先行后列的输出过程中，原字符串的顺序也是从左到右的，
可以设一个k记录当前字符串的位置，便于找到要输出的字符。
*/

int main(int argc, char *argv[]) {
  int n, m, N;
  char str[MAXN];
  int i, j, k;

  scanf("%s", str);
  N = strlen(str);
  n = (N + 2) / 3;
  m = N + 2 - 2 * n;

  //	printf("n=%d, m=%d\n", n, m);

  k = 0;
  for (i = 0; i < n; ++i) {
    if (i != n - 1) {
      // 前n-1行的打印。
      for (j = 0; j < m; ++j) {
        if (j == 0) {
          putchar(str[k]);
        } else if (j == m - 1) {
          putchar(str[N - 1 - k]);
        } else {
          putchar(' ');
        }
      }
      ++k; // 每打一行
    } else {
      // 最后一行的打印
      for (j = 0; j < m; ++j) {
        putchar(str[k++]);
      }
    }
    putchar('\n');
  }
  return 0;
}
