#include <stdio.h>
#include <stdlib.h>

/*
输入
输入第一行表示测试用例的个数m，接下来m行每行有3个用空格隔开的整数，分别表示年月日。测试数据不会有闰年。

输出
输出m行。按xxxx-xx-xx的格式输出，表示输入日期的后一天的日期。
*/

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
const int Days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Time {
  int yy, mm, dd;

  // 加一天。
  void Add() {
    ++dd;
    if (dd == Days[mm] + 1) {
      dd = 1;
      ++mm;
    }
    if (mm == 13) {
      mm = 1;
      ++yy;
    }
  }

  void Print() { printf("%04d-%02d-%02d\n", yy, mm, dd); }
};

int main(int argc, char *argv[]) {
  int m;

  while (scanf("%d", &m) != EOF) {
    while (m--) {
      Time t;
      scanf("%d%d%d", &t.yy, &t.mm, &t.dd);
      t.Add();
      t.Print();
    }
  }
  return 0;
}
