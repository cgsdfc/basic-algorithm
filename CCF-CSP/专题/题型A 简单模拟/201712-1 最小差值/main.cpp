#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
先排序，然后最小差值必定在相邻两个数之间产生，
时间复杂度 NlogN.
*/

int N;
#define MAXN 1005

int a[MAXN];
// 这个值的设定是根据输入每个元素x的最大值。
const int INF = 100000;

int main(int argc, char **argv) {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a, a + N);
  int ans = INF;
  for (int i = 0; i < N - 1; ++i) {
    int diff = a[i + 1] - a[i];
    if (diff < ans) {
      ans = diff;
    }
    if (ans == 0) {
      break; // 绝对值的最小是0.
    }
  }
  printf("%d\n", ans);

  return 0;
}
