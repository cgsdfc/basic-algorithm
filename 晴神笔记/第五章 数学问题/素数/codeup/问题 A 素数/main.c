#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN (10000 + 5)
int p[MAXN];
int ans[MAXN];

void FindPrime(void) {
  int i, j;
  for (i = 2; i < MAXN; ++i) {
    if (!p[i]) {
      for (j = 2 * i; j < MAXN; j += i) {
        p[j] = 1;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int n;

  FindPrime();
  while (scanf("%d", &n) != EOF) {
    int i;
    int k = 0;
    int flag = 1;

    for (i = 2; i < n; ++i) {
      if (!p[i] && i % 10 == 1) {
        if (flag) {
          flag = 0;
        } else {
          putchar(' ');
        }
        ++k;
        printf("%d", i);
      }
    }
    if (k == 0) {
      printf("-1");
    }
    putchar('\n');
  }
  return 0;
}
