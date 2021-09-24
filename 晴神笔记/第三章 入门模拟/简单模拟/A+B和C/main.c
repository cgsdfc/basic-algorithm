#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef long long LL;

int main(int argc, char *argv[]) {
  int T;
  int i;

  scanf("%d", &T);
  i = 1;
  while (T--) {
    LL a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    printf("Case #%d: %s\n", i, (a + b > c) ? "true" : "false");
    i++;
  }
}
