#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

void Strcat(char a[], char b[], char c[]) {
  while (*a) {
    *c = *a;
    ++c;
    ++a;
  }
  while (*b) {
    *c = *b;
    ++c;
    ++b;
  }
  *c = 0;
}

#define MAXN 105

int main(int argc, char *argv[]) {
  char a[MAXN], b[MAXN];

  while (scanf("%s%s", a, b) != EOF) {
    char c[2 * MAXN];
    Strcat(a, b, c);
    puts(c);
  }
  return 0;
}
