#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
当N=N时，要用到2N-1个斐波那契数（从0开始）。
注意各种数量的对应关系，比如输入的N和最大的斐波那契数的关系，
输出的空格和第i行的关系，第i行和改行要输出的数的多少的关系。
还有就是N不超过10，表示N最大10.
*/

#define MAXN 10
#define MAXM (MAXN * 2)

int a[MAXM];

void Fill(int n) {
  int i;
  a[0] = 0;
  a[1] = 1;
  for (i = 2; i <= n; ++i) {
    a[i] = a[i - 1] + a[i - 2];
  }
}

void Print(int n) {
  int i;
  for (i = 0; i < n; ++i) {
    // 打印空格。
    int space = 2 * (n - i - 1);
    int j;
    while (space--) {
      putchar(' ');
    }
    for (j = 0; j < 2 * i + 1; ++j) {
      printf("%d%s", a[j], j == 2 * i ? "\n" : " ");
    }
  }
}

int main(int argc, char *argv[]) {
  int M;
  int i;

  Fill(2 * MAXN - 2);

  scanf("%d", &M);
  while (M--) {
    int N;
    scanf("%d", &N);
    Print(N);
  }

  return 0;
}
