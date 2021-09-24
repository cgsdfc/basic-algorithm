#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1005
typedef struct Big {
  int d[MAXN];
  int len;
} Big;

char str[MAXN];

Big From(char str[]) {
  int i;
  int len = strlen(str);
  Big c;

  c.len = len;
  for (i = 0; i < len; ++i) {
    c.d[i] = str[len - 1 - i] - '0';
  }
  return c;
}

Big Div(Big a, int b, int *rem) {
  int r = 0;
  int i;
  Big c;

  c.len = a.len;
  for (i = a.len - 1; i >= 0; --i) {
    r = r * 10 + a.d[i];
    if (r < b) {
      c.d[i] = 0;
    } else {
      c.d[i] = r / b;
      r %= b;
    }
  }
  while (c.len - 1 >= 1 && c.d[c.len - 1] == 0) {
    c.len--;
  }
  *rem = r;
  return c;
}

void Print(Big c) {
  int i;
  for (i = c.len - 1; i >= 0; --i) {
    printf("%d", c.d[i]);
  }
  //	printf("\n");
}

int main(int argc, char *argv[]) {
  Big a = {};
  Big c = {};
  int b;
  int r;

  scanf("%s%d", str, &b);
  a = From(str);
  c = Div(a, b, &r);
  Print(c);
  printf(" %d\n", r);

  return 0;
}
