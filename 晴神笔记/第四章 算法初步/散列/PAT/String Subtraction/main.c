#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
#define MAXN 10005

char str[MAXN], str2[MAXN];
int hashtable[256];

int main(int argc, char *argv[]) {
  int i, len;

  gets(str);  // S1
  gets(str2); // S2

  for (i = 0, len = strlen(str2); i < len; ++i) {
    hashtable[str2[i]] = 1;
  }
  // S1-S2
  for (i = 0, len = strlen(str); i < len; ++i) {
    if (!hashtable[str[i]]) {
      putchar(str[i]);
    }
  }
  putchar('\n');
  return 0;
}
