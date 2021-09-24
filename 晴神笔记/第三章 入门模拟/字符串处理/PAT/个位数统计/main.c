#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1010

int cnt[15];

int main(int argc, char *argv[]) {
  char str[MAXN];
  int i;
  int len;

  scanf("%s", str);
  len = strlen(str);
  for (i = 0; i < len; ++i) {
    int num = str[i] - '0';
    cnt[num]++;
  }
  for (i = 0; i < 10; ++i) {
    if (cnt[i]) {
      printf("%d:%d\n", i, cnt[i]);
    }
  }
  return 0;
}
