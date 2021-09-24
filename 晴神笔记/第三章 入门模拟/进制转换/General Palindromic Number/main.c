#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
32位整数可占的最大位数。
*/

#define MAXN 40

int Judge(int a[], int n) {
  int i;
  for (i = 0; i < n / 2; ++i) {
    if (a[i] != a[n - 1 - i])
      return 0;
  }
  return 1;
}

int main(int argc, char *argv[]) {
  int n, b;
  int a[MAXN];
  int k = 0;
  int ans;

  scanf("%d%d", &n, &b);
  do {
    a[k++] = n % b;
    n /= b;
  } while (n);

  ans = Judge(a, k);
  printf("%s\n", ans ? "Yes" : "No");
  while (k--) {
    printf("%d", a[k]);
    // 最后一轮，k==0
    printf("%s", k ? " " : "\n");
  }
  return 0;
}
