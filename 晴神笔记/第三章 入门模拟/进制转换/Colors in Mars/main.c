#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

const char digs[] = "0123456789ABC";

int main(int argc, char *argv[]) {
  int a[3];
  int i;
  char c[10];
  int k = 0;

  for (i = 0; i < 3; ++i)
    scanf("%d", &a[i]);
  for (i = 0; i < 3; ++i) {
    int x = a[i];
    c[k++] = digs[x / 13];
    c[k++] = digs[x % 13];
  }
  c[k++] = 0;
  printf("#%s\n", c);

  return 0;
}
