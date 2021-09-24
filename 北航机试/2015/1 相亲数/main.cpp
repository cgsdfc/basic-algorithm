#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
求一个数全部的约数，从小到大输出。
*/
void Factor(int n, vector<int> &vi) {
  int sqr = sqrt(n);
  for (int i = 1; i <= sqr; ++i) {
    // 注意，n本身不算。
    if (n % i == 0) {
      vi.push_back(i);
      int p = n / i;
      if (p != i && p != n) {
        vi.push_back(p);
      }
    }
  }
  sort(vi.begin(), vi.end());
}

int Print(int n) {
  // 打印因子和。
  printf("%d, ", n);
  int sum = 0;
  vector<int> vi;
  Factor(n, vi);
  for (int i = 0; i < vi.size(); ++i) {
    sum += vi[i];
    printf("%d%s", vi[i], i == vi.size() - 1 ? "=" : "+");
  }
  printf("%d\n", sum);
  return sum;
}

int main(int argc, char **argv) {
  int a, b;
  scanf("%d%d", &a, &b);
  int aa = Print(a);
  int bb = Print(b);
  bool ans = (aa == b && bb == a);
  printf("%d\n", (int)ans);

  return 0;
}
