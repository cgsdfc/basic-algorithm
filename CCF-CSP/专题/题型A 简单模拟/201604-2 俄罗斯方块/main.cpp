#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
设置一个数组表示图形的每一个像素的当前行，
每次检查1像素的下一行是否在背景中有1像素，如有则终止。
*/

const int Row = 15, Col = 10;
const int N = 4;

int bg[20][20];
int a[10][10];

int row, col; // a的左上角的坐标。
int low;

void Solve() {
  /*
  注意，只要方块的最下面一个不碰到底部，就可以继续下落。
  */
  while (low < Row) {
    bool ok = true;
    for (int i = row; i < row + N; ++i) {
      for (int j = col; j < col + N; ++j) {
        if (!a[i - row + 1][j - col + 1])
          continue;
        if (i < Row && bg[i + 1][j]) {
          ok = false;
          break; // 碰到下边缘。
        }
      }
    }
    if (ok) {
      ++row;
      ++low;
    } else {
      break;
    }
  }
  //	printf("row %d col %d low %d \n",row,col, low);

  // 把a直接写入bg，然后输出。
  for (int i = row; i < row + N; ++i) {
    for (int j = col; j < col + N; ++j) {
      int x = a[i - row + 1][j - col + 1];
      if (x) {
        // 1值都在low以上，而low在Row以上，所以这里不会越界。
        bg[i][j] = x;
      }
    }
  }
  for (int i = 1; i <= Row; ++i) {
    for (int j = 1; j <= Col; ++j) {
      printf("%d%s", bg[i][j], j == Col ? "\n" : " ");
    }
  }
}

int FindLow() {
  for (int i = N; i >= 1; i--) {
    for (int j = 1; j <= N; ++j) {
      if (a[i][j])
        return i;
    }
  }
  return -1;
}

int main(int argc, char **argv) {
  for (int i = 1; i <= Row; ++i) {
    for (int j = 1; j <= Col; ++j) {
      scanf("%d", &bg[i][j]);
    }
  }
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  // 初始位置。
  row = 1;
  scanf("%d", &col);
  low = FindLow();

  Solve();

  return 0;
}
