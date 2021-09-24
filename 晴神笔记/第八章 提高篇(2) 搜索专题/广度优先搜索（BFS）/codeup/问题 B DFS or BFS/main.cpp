#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
先基于当前迷宫做出动作，即在当前迷宫里安全的动作。
然后迷宫切到下一个状态。
*/

#define MAXN 10
const int N = 8;     // 固定大小的迷宫。
char A[MAXN][MAXN];  // 迷宫。
int inq[MAXN][MAXN]; // 标记走过的路。
bool ans;

struct Point {
  int x;
  int y;
  bool operator==(Point p) { return x == p.x && y == p.y; }
};

const Point in = {7, 0};  // 左下角。
const Point out = {0, 7}; // 右上角。

// 9 个动作。
const Point Dir[9] = {{0, 1},   {0, -1}, {1, 0}, {-1, 0}, {-1, 1},
                      {-1, -1}, {1, -1}, {1, 1}, {0, 0}};

void Print(void) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      printf("%c", A[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

bool HasStone(void) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (A[i][j] == 'S')
        return true;
    }
  }
  return false;
}

void DFS(Point now) {
  if (A[now.x][now.y] == 'S') {
    // 走到一个地方，然后石头掉下来。
    return;
  }
  if (now == out) {
    // 走到了出口，并且没有石头。
    ans = true;
    return;
  }
  /*
  如果石头全部消失了，那么必定可以到达。
  */
  if (!HasStone()) {
    ans = true;
    return;
  }

  /*
  基于当前迷宫找到安全动作。
  然后刷新迷宫（备份到temp）。
  */
  Point points[10];
  int len = 0;
  for (int i = 0; i < 9; ++i) {
    Point v = {now.x + Dir[i].x, now.y + Dir[i].y};
    if (0 <= v.x && v.x < N && 0 <= v.y && v.y < N && A[v.x][v.y] != 'S' &&
        (!inq[v.x][v.y] || (!Dir[i].x && !Dir[i].y))) {
      points[len++] = v;
    }
  }
  /*
  原地不动总是安全的，所以必定有一个方案。
  */
  assert(len);

  /*
  令石头下落。就是用前一行覆盖当前行，第0行全部为平地。
  起点终点的标记不重要。
  */
  char temp[MAXN][MAXN];
  for (int i = N - 1; i >= 0; --i) {
    if (i == 0) {
      for (int j = 0; j < N; ++j) {
        A[i][j] = '.';
      }
    } else {
      for (int j = 0; j < N; ++j) {
        A[i][j] = A[i - 1][j];
      }
    }
  }

  memcpy(temp, A, sizeof(temp));
  for (int i = 0; i < len; ++i) {
    Point p = points[i];
    inq[p.x][p.y] = 1;
    DFS(p);
    memcpy(A, temp, sizeof(temp));
    inq[p.x][p.y] = 0;
  }
}

int main(int argc, char **argv) {
  int T;

#ifndef ONLINE_JUDGE
  freopen("./in.txt", "r", stdin);
#endif

  scanf("%d", &T);

  for (int k = 1; k <= T; ++k) {
    for (int i = 0; i < N; ++i) {
      getchar();
      for (int j = 0; j < N; ++j) {
        A[i][j] = getchar();
      }
    }
    getchar();
    //		continue;

    ans = false;
    memset(inq, 0, sizeof(inq));
    DFS(in);
    /*
    Case #1: Yes
    Case #2: No
    */
    printf("Case #%d: %s\n", k, ans ? "Yes" : "No");
  }
  return 0;
}
