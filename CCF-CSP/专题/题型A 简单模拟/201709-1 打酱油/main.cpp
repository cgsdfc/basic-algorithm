#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int N;

int main(int argc, char **argv) {
  scanf("%d", &N);
  int ans = 0;
  ans += (N / 50) * 7; // 每花50，得到7瓶。
  N %= 50;
  ans += (N / 30) * 4; // 每花30，得到4瓶。
  N %= 30;
  ans += N / 10;
  printf("%d\n", ans);

  return 0;
}
