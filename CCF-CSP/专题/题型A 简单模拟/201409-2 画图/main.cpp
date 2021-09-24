#include <cstdio>

/*
用一个bool矩阵记录哪些点被涂色即可。
用的是散列的思想。
*/

// 坐标是非负整数，最大100.
#define MAXN 105

bool A[MAXN][MAXN];

struct Point {
  int X, Y;
};

struct Retangle {
  Point up, down;

  void Draw() {
    // 注意，一个单位方格用它左下角的点坐标表示。
    for (int i = down.X; i < up.X; ++i) {
      for (int j = down.Y; j < up.Y; ++j) {
        A[i][j] = true;
      }
    }
  }
};

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int N;

int main(int argc, char **argv) {
  scanf("%d", &N);
  while (N--) {
    Retangle r;
    scanf("%d%d%d%d", &r.down.X, &r.down.Y, &r.up.X, &r.up.Y);
    r.Draw();
  }
  int ans = 0;
  for (int i = 0; i < MAXN; ++i) {
    for (int j = 0; j < MAXN; ++j) {
      if (A[i][j]) {
        ++ans;
      }
    }
  }
  printf("%d\n", ans);

  return 0;
}
