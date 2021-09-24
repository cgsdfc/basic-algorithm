#include <stdio.h>
#include <stdlib.h>

#define MAXN 20
typedef struct Location {
  int x, y; // 当前位置的行，列。
} Location;

int N, M;          // 迷宫的行数，列数。
int A[MAXN][MAXN]; // 迷宫，0表示输入的0，即不通，1表示通并且没走过，2表示走过。
Location in, out;  // 入口，出口。
int has;           // 是否有解。

/*
一条道路的最大长度，是覆盖了迷宫的所有点。
*/
#define MAXP 400

struct {
  Location data[MAXP];
  int len;
} path;

// 顺序：左上右下。
const Location Dir[] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

int Min(int a, int b) { return a < b ? a : b; }
int Max(int a, int b) { return a > b ? a : b; }

void DFS(Location now) {
  int i;
  int j;
  Location a, b;

  if (now.x == out.x && now.y == out.y) {
    // 达到出口，输出路径。
    for (i = 0; i < path.len; ++i) {
      printf("(%d,%d)%s", path.data[i].x, path.data[i].y,
             i == path.len - 1 ? "\n" : "->");
    }
    has = 1;
    return;
  }

  /*
  剪枝逻辑：
  检查当前位置now到终点out之间的矩阵里，是否存在一行或一列不通，
  即整行都没有1，如果有，则肯定不能从now达到out。
  */
#if 0	 
	a.x=Min(now.x, out.x);
	a.y=Min(now.y, out.y);
	b.x=Max(now.x, out.y);
	b.y=Max(now.y, out.y);
	
	for (i=a.x;i<=b.x;++i) {
		int ok=0;
		for (j=a.y;j<=b.y;++j) {
			if (A[i][j] == 1) {
				ok=1;
				break;
			}
		}
		if (!ok) {
			// 有一堵墙。即一行都不通。
			return; 
		}
	}
	for (j=a.y;j<=b.y;++j) {
		int ok=0;
		for (i=a.x;i<=b.x;++i) {
			if (A[i][j] == 1) {
				ok=1;
				break;
			}
		}
		if (!ok) {
			// 有一列不通。
			return; 
		}
	}
#endif

  for (i = 0; i < 4; ++i) {
    Location next = {now.x + Dir[i].x, now.y + Dir[i].y};
    // 检查next是否可走。
    if (1 <= next.x && next.x <= N && 1 <= next.y && next.y <= M &&
        A[next.x][next.y] == 1) {
      A[next.x][next.y] = 2; // 走过。
      path.data[path.len++] = next;
      DFS(next);
      --path.len;
      A[next.x][next.y] = 1; // 可走。
    }
  }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
  freopen("./in.txt", "r", stdin);
#endif

  while (scanf("%d%d", &N, &M) != EOF) {
    int i;
    for (i = 1; i <= N; ++i) {
      int j;
      for (j = 1; j <= M; ++j) {
        scanf("%d", &A[i][j]);
      }
    }
    scanf("%d%d", &in.x, &in.y);
    scanf("%d%d", &out.x, &out.y);
    has = 0;
    path.len = 1;
    path.data[0] = in;
    A[in.x][in.y] = 2;
    DFS(in);
    if (!has) {
      puts("-1");
    }
  }
  return 0;
}
