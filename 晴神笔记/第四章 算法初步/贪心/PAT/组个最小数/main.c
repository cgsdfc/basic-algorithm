#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int count[10];

int main(int argc, char *argv[]) {
  int i;

  for (i = 0; i < 10; ++i) {
    scanf("%d", &count[i]);
  }
  for (i = 1; i < 10; ++i) {
    if (count[i]) {
      --count[i];
      printf("%d", i);
      break;
    }
  }
  for (i = 0; i < 10; ++i) {
    int j;
    for (j = 0; j < count[i]; ++j) {
      printf("%d", i);
    }
  }
  return 0;
}
