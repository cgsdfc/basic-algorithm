#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct Info {
  char name[15];
  char id[15];
  int score;
} Info;

Info Max, Min;

void Print(Info *i) { printf("%s %s\n", i->name, i->id); }

int main(int argc, char *argv[]) {
  int i, n;

  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    Info tmp;
    scanf("%s %s %d", tmp.name, tmp.id, &tmp.score);
    if (i == 0 || tmp.score > Max.score) {
      Max = tmp;
    }
    if (i == 0 || tmp.score < Min.score) {
      Min = tmp;
    }
  }
  Print(&Max);
  Print(&Min);

  return 0;
}
