#include <iostream>
#include <utility>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  int N;
  while (scanf("%d", &N), N != 0) {
    while (N--) {
      // 一个点以一个pair表示。
      pair<double, double> p, ans(0, 0);
      for (int i = 0; i < 3; ++i) {
        cin >> p.first >> p.second;
        ans.first += p.first;
        ans.second += p.second;
      }
      printf("%.1f %.1f\n", ans.first / 3, ans.second / 3);
    }
  }
  return 0;
}
