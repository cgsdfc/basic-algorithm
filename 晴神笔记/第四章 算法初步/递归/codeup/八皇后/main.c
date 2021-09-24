#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100

int all[MAXN][10];
int N;
// 存放临时生成的一个解。
int P[10];
int hashtable[10];

/*
注意，解决八皇后问题时，最好要么统一用0开始的下标，
要么统一用1开始的下标，后者把数组开大一些即可。
*/

// 按字典序找出八皇后的所有解。
void FindAll(int index) {
  if (index == 9) {
    // 递归出口，已经生成一个排列。
    int i, j;
    int ok = 1;
    for (i = 1; i <= 8; ++i) {
      for (j = i + 1; j <= 8; ++j) {
        // i行， Pi列；j行，Pj列。
        if (abs(i - j) == abs(P[i] - P[j])) {
          // 处于同一个对角线
          ok = 0;
          break;
        }
      }
    }
    if (ok) {
      for (i = 0; i < 8; ++i) {
        all[N][i] = P[i];
      }
      ++N;
    }
    return;
  }
  // 第index个皇后应该放在哪一列。
  int i;
  for (i = 1; i <= 8; ++i) {
    if (!hashtable[i]) {
      P[index] = i;
      hashtable[i] = 1;
      FindAll(index + 1);
      hashtable[i] = 0;
    }
  }
}

int main(int argc, char *argv[]) {
  int n;
  int i;

  freopen("./in.txt", "r", stdin);
  FindAll(1);

  //	printf("%d\n", N);
  //	for (i=0;i<N;++i) {
  //		int j;
  //		for (j=1;j<=8;++j) {
  //			printf("%d ", all[i][j]);
  //		}
  //		puts("");
  //	}

  while (scanf("%d", &n) != EOF) {
    while (n--) {
      int b;
      int i;
      scanf("%d", &b);
      for (i = 1; i <= 8; ++i) {
        printf("%d", all[b - 1][i]);
      }
      printf("\n");
    }
  }
  return 0;
}
