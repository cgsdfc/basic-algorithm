#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
题目描述
设计一个程序能计算一个日期加上若干天后是什么日期。

输入
输入第一行表示样例个数m，接下来m行每行四个整数分别表示年月日和累加的天数。

输出
输出m行，每行按yyyy-mm-dd的个数输出。

样例输入 Copy
1
2008 2 3 100
样例输出 Copy
2008-05-13
*/

int MonDays(int yy, int mm) {
  int leap = (yy % 4 == 0 && yy % 100 != 0) || (yy % 400 == 0);
  switch (mm) {
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    return 31;
  case 4:
  case 6:
  case 9:
  case 11:
    return 30;
  case 2:
    return 28 + leap;
  default:
    return -1;
  }
}

int main(int argc, char *argv[]) {
  int m;

  while (scanf("%d", &m) != EOF) {
    while (m--) {
      int yy, mm, dd;
      int n;

      scanf("%d%d%d%d", &yy, &mm, &dd, &n);
      while (n--) {
        ++dd;
        if (dd == MonDays(yy, mm) + 1) {
          dd = 1;
          ++mm;
        }
        if (mm == 13) {
          mm = 1;
          ++yy;
        }
      }
      printf("%04d-%02d-%02d\n", yy, mm, dd);
    }
  }
  return 0;
}
