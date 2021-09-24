#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct Time {
  int hh;
  int mm;
  int ss;
} Time;

int Cmp(Time *a, Time *b) {
  if (a->hh != b->hh)
    return a->hh - b->hh;
  if (a->mm != b->mm)
    return a->mm - b->mm;
  return a->ss - b->ss;
}

#define MAXN 20

typedef struct Record {
  Time in;
  Time out;
  char id[MAXN];
} Record;

Time ReadTime(void) {
  Time t;
  scanf("%d:%d:%d", &t.hh, &t.mm, &t.ss);
  return t;
}

// 最早signin的人,最晚signout的人.
Record MinIn, MaxOut;

int main(int argc, char *argv[]) {
  int n;
  int i;

  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    Record r;
    scanf("%s", r.id);
    r.in = ReadTime();
    r.out = ReadTime();
    // 为了避免设置最大或最小时间
    if (i == 0 || Cmp(&r.in, &MinIn.in) < 0) {
      MinIn = r;
    }
    if (i == 0 || Cmp(&r.out, &MaxOut.out) > 0) {
      MaxOut = r;
    }
  }
  // unlock, lock.
  printf("%s %s\n", MinIn.id, MaxOut.id);
  return 0;
}
