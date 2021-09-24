#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct Cake {
  double store; // 库存
  double total; // 总售价
  double cost;  // 单价
} Cake;

#define MAXN 1005

Cake cakes[MAXN];

int CMP(const void *_a, const void *_b) {
  Cake *a = (Cake *)_a;
  Cake *b = (Cake *)_b;
  return a->cost == b->cost ? 0 : (a->cost > b->cost ? -1 : 1);
}

int main(int argc, char *argv[]) {
  int N;
  double D;
  int i;
  double ans = 0;

  scanf("%d%lf", &N, &D);
  for (i = 0; i < N; ++i) {
    scanf("%lf", &cakes[i].store);
  }
  for (i = 0; i < N; ++i) {
    scanf("%lf", &cakes[i].total);
    cakes[i].cost = cakes[i].total / cakes[i].store;
  }
  qsort(cakes, N, sizeof(Cake), CMP);
  /*
  每次总是选单价最高的月饼来满足需求，
  直到需求被满足。
  */
  for (i = 0; i < N; ++i) {
    if (cakes[i].store <= D) {
      D -= cakes[i].store;
      ans += cakes[i].total;
    } else {
      ans += D * cakes[i].cost;
      break;
    }
  }
  printf("%.2f\n", ans);

  return 0;
}
