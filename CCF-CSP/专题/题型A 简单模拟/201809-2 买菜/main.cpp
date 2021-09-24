#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
类似合并两个有序序列。
*/

struct Interval {
  int L, R;
  int len() { return R - L; }
  bool operator<(Interval a) {
    if (L != a.L)
      return L < a.L;
    return R < a.R;
  }
};

#define MAXN 2005
int N;
Interval A[MAXN], B[MAXN];

void Read(Interval a[]) {
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &a[i].L, &a[i].R);
  }
}

// a包含b。
bool Include(Interval &a, Interval &b) { return a.L <= b.L && b.R <= a.R; }

// a < b
bool Less(Interval &a, Interval &b) { return a.R <= b.L; }

bool Overlap(Interval &a, Interval &b) { return (a.L <= b.L && b.L <= a.R); }

int Compute(Interval a, Interval b) {
  int L = max(a.L, b.L);
  int R = min(a.R, b.R);
  return max(0, R - L);
}

void Solve() {
  // 数据量较小，可以直接用平方复杂度算法。
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      int len = Compute(A[i], B[j]);
      ans += len;
    }
  }
  printf("%d\n", ans);
}

/*
线性复杂度的解法，就是归并逻辑比较复杂。
使用2-pointer法，注意指针后移的条件。
一个指针后移的条件是：

当前所指区间不可能与另一个序列的当前指针之后的任何区间发生交集。

当两个指针都满足上述条件时，移动其中一个即可。

当数据量较大时，这个算法具有优势。
*/
void Solve2() {
  int ans = 0;
  int i = 0, j = 0;

  while (i < N && j < N) {
    Interval a = A[i], b = B[j];
    int len = Compute(a, b);
    ans += len;
    if (!len) {
      // 两个区间不相交。
      if (a.R <= b.L) {
        // a 在左边。
        ++i;
      } else {
        // a 在右边。
        ++j;
      }
    } else {
      if (len == a.len()) {
        // a包含于b。
        ++i;
      } else if (len == b.len()) {
        // b包含于a。
        ++j;
      } else if (a.L < b.L) {
        // ab呈交错状。
        // a在左边。
        ++i;
      } else {
        // a在右边。
        ++j;
      }
    }
  }
  printf("%d\n", ans);
}

int main(int argc, char **argv) {
  scanf("%d", &N);
  Read(A);
  Read(B);
  Solve2();
  return 0;
}
