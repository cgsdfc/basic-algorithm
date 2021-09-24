#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
数据量较小，直接模拟，O(NK)。
*/

#define MAXT 1005
int T; // 序列的长度。
int K; // 判定为“逗留”的阈值。
int N; // N个人。

struct Point {
  int X, Y;
};

Point where[MAXT]; // 一个居民的轨迹。
Point up, down;    // 风险地区的矩形区域。

// 判定p是否经过风险区，点落在矩形内，包括边界。
bool In(Point &p) {
  // 注意up的全部坐标都是最大的，down则最小。
  return down.X <= p.X && p.X <= up.X && down.Y <= p.Y && p.Y <= up.Y;
}

int MaxLen() {
  // 计算一个居民在风险区的最大连续序列长度。
  int i = 0;
  int ans = -1;

  while (i < T) {
    while (i < T && !In(where[i])) {
      i++;
    }
    int j = i;
    while (j < T && In(where[j])) {
      j++;
    }
    int len = j - i;
    if (len > ans) {
      ans = len;
    }
    i = j;
  }
  return ans;
}

int in;   // 经过。
int stay; // 逗留。

int main(int argc, char **argv) {
  scanf("%d%d%d", &N, &K, &T);
  scanf("%d%d%d%d", &down.X, &down.Y, &up.X, &up.Y);

  while (N--) {
    // N个人的轨迹。
    for (int i = 0; i < T; ++i) {
      scanf("%d%d", &where[i].X, &where[i].Y);
    }
    int len = MaxLen();
    if (len > 0) {
      ++in;
    }
    if (len >= K) {
      ++stay;
    }
  }
  printf("%d\n", in);
  printf("%d\n", stay);

  return 0;
}
