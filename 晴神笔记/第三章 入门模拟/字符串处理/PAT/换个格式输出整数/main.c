#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 10

int main(int argc, char *argv[]) {
  char str[MAXN];
  int len;
  int i;

  scanf("%s", str);
  len = strlen(str);
  for (i = 0; i < len; ++i) {
    int p = len - i;
    int num = str[i] - '0';
    if (p == 3) {
      // 百位
      while (num--)
        putchar('B');
    } else if (p == 2) {
      // 十位
      while (num--)
        putchar('S');
    } else {
      // 个位
      int j;
      for (j = 1; j <= num; ++j)
        printf("%d", j);
    }
  }
  putchar('\n');

  return 0;
}
