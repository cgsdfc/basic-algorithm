#include <cstdio>
//#include <algorithm>
// 注意不需要排序，题目保证index升序。
using namespace std;

// 数据范围超过了int，但在ll之内。
typedef long long ll;

struct Node {
  ll index;
  ll value;
};

#define MAXL (5 * 100000 + 5)

// 两个向量，大小和N无关。
struct Vector {
  Node data[MAXL];
  int len;
} a, b;

void Read(Vector &a) {
  for (int i = 0; i < a.len; ++i) {
    scanf("%lld%lld", &a.data[i].index, &a.data[i].value);
  }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  ll ans = 0;
  int N;
  scanf("%d%d%d", &N, &a.len, &b.len);
  Read(a);
  Read(b);
  // 实际的项数在int内。
  int i = 0;
  int j = 0;
  while (i < a.len && j < b.len) {
    if (a.data[i].index == b.data[j].index) {
      ans += a.data[i].value * b.data[j].value;
      ++i;
      ++j;
    } else if (a.data[i].index < b.data[j].index) {
      ++i;
    } else {
      ++j;
    }
  }
  printf("%lld\n", ans);

  return 0;
}
