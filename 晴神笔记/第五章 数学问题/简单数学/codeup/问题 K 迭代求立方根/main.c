#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
/*
题目描述

立方根的逼近迭代方程是 y(n+1) = y(n)*2/3 +
x/(3*y(n)*y(n)),其中y0=x.求给定的x经过n次迭代后立方根的值。


输入

输入有多组数据。
每组一行，输入x n。


输出

迭代n次后的立方根，double精度,保留小数点后面六位。


样例输入 Copy
4654684 1
65461 23
样例输出 Copy
3103122.666667
40.302088
*/

int main(int argc, char *argv[]) {
  int x, n;
  while (scanf("%d%d", &x, &n) != EOF) {
    double y = x;
    while (n--) {
      y = y * 2 / 3 + x / (3 * y * y);
    }
    printf("%.6f\n", y);
  }
  return 0;
}
