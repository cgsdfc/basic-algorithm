#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct Info {
  char dig[25];
  int k;
  int v;
} Info;

#define MAXN 1005

Info info[MAXN];

void Find(int k, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    if (info[i].k == k) {
      printf("%s %d\n", info[i].dig, info[i].v);
      return;
    }
  }
}

int main(int argc, char *argv[]) {
  int n;
  int i;
  int m;

  freopen("./in.txt", "r", stdin);

  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%s %d %d", info[i].dig, &info[i].k, &info[i].v);
  }
  scanf("%d", &m);
  for (i = 0; i < m; ++i) {
    int k;
    scanf("%d", &k);
    Find(k, n);
  }
  return 0;
}
