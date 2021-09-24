#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 3

typedef struct Bet {
  double odd;
  int res;
} Bet;

Bet bets[MAXN];

Bet DoBet(double odds[]) {
  int i;
  Bet b;

  b.odd = -1;
  b.res = 0;
  for (i = 0; i < MAXN; ++i) {
    if (odds[i] > b.odd) {
      b.odd = odds[i];
      b.res = i;
    }
  }
  return b;
}

int main(int argc, char *argv[]) {
  int n = 0;
  int i;
  int j;
  double odds[MAXN];
  char map[] = "WTL";
  double p = 1;

  for (i = 0; i < MAXN; ++i) {
    // 读入一个game.
    for (j = 0; j < MAXN; ++j) {
      scanf("%lf", &odds[j]);
    }
    // 获取bet结果.
    bets[n++] = DoBet(odds);
  }

  for (i = 0; i < n; ++i) {
    p *= bets[i].odd;
    printf("%c ", map[bets[i].res]);
  }
  printf("%.2f\n", (p * 0.65 - 1) * 2);

  return 0;
}
