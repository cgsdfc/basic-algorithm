#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 90

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char *argv[]) {
  char str[MAXN];
  char ans[MAXN][MAXN];
  int len;
  int i;
  int m = 0, n = 0;

  gets(str);
  len = strlen(str);
  for (i = 0; i < len; ++i) {
    char c = str[i];
    if (c == ' ') {
      ans[n][m] = 0;
      m = 0;
      ++n;
    } else {
      ans[n][m++] = c;
    }
  }

  // ���һ������ĩβû�пո�
  ans[n][m] = 0;
  ++n;

  for (i = n - 1; i >= 0; --i) {
    // ע�⣬��λ����ĵ�һά��char[]
    printf("%s%s", ans[i], i == 0 ? "\n" : " ");
  }
  return 0;
}
