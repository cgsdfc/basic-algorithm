#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXM 10005
#define MAXN 100005

int hashtable[MAXM];
int bets[MAXN];

int Find(int n) {
  int i;
  for (i = 0; i < n; ++i) {
    int x = bets[i];
    if (hashtable[x] == 1) {
      // 只出现了一次的bet，是Unique。
      return x;
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {
  int N;
  int i;
  int win;

  scanf("%d", &N);
  for (i = 0; i < N; ++i) {
    int x;
    scanf("%d", &x);
    hashtable[x]++;
    bets[i] = x;
  }
  win = Find(N);
  if (win != -1) {
    printf("%d\n", win);
  } else {
    puts("None");
  }

  return 0;
}
