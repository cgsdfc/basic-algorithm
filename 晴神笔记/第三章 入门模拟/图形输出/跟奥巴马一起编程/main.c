#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

void Print(char c, int n) {
  int i;
  for (i = 0; i < n; ++i)
    putchar(c);
  putchar('\n');
}

int main(int argc, char *argv[]) {
  int n;
  char c;
  int row, col;
  int i, j;

  scanf("%d %c", &n, &c);
  col = n;
  // 行是n除以2,再四舍五入.若是偶数则整除,若是奇数则必定进一.
  row = n / 2 + n % 2;
  i = row - 2;

  Print(c, col);
  while (i--) {
    putchar(c);
    j = col - 2;
    while (j--)
      putchar(' ');
    putchar(c);
    putchar('\n');
  }
  Print(c, col);

  return 0;
}
