#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int N;

int main(int argc, char **argv) {
  scanf("%d", &N);
  int ans = 0;
  ans += (N / 50) * 7; // ÿ��50���õ�7ƿ��
  N %= 50;
  ans += (N / 30) * 4; // ÿ��30���õ�4ƿ��
  N %= 30;
  ans += N / 10;
  printf("%d\n", ans);

  return 0;
}
