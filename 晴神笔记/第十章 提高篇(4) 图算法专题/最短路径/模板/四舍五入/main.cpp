#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
printf的%.mf是截断式的，不是四舍五入。
要实现四舍五入，必须手工或者用C++的流。
*/

/*
靠C++流实现四舍五入保留N位小数，因为cout用起来比较容易错，建议封装成函数。
向stdout输出一个浮点数x，四舍五入保留n位小数。

当n=1时，不会四舍五入，不知道为什么？
*/
void PrintFloat(double x, int n) {
  cout.flags(ios::fixed);
  cout.precision(n);
  cout << x;
}

/*
利用cmath实现。
Round实现四舍五入保留n位，但是输出要自己用printf。
*/
double Round(double x, int n) {
  double p = pow(10, n);
  x = round(x * p) / p;
  return x;
}

int main(int argc, char **argv) {
  double x;
  int n;

  while (cin >> x >> n) {
    PrintFloat(x, n);
    puts("");
  }
  return 0;
}
