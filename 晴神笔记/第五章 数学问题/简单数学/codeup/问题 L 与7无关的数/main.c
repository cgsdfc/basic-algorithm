#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int Judge(int x) {
  if (x % 7 == 0)
    return 1;
  while (x) {
    if (x % 10 == 7)
      return 1;
    x /= 10;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int n;
  while (scanf("%d", &n) != EOF) {
    int i;
    int ans = 0;
    for (i = 1; i <= n; ++i) {
      if (Judge(i))
        continue;
      ans += i * i;
    }
    printf("%d\n", ans);
  }
  return 0;
}
