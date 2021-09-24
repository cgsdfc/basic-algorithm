#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct Time {
  int year;
  int month;
  int day;
} Time;

typedef struct Man {
  Time bir;
  char name[10];
} Man;

const Time Day = {1814, 9, 6};
const Time Today = {2014, 9, 6};

int Cmp(Time *a, Time *b) {
  if (a->year != b->year)
    return a->year - b->year;
  if (a->month != b->month)
    return a->month - b->month;
  return a->day - b->day;
}

// �� Day �������֮���,��Today�������֮ǰ������,�Ϸ�.
int Valid(Time *t) { return Cmp(t, &Day) >= 0 && Cmp(t, &Today) <= 0; }

int More(Time *a, Time *b) { return Cmp(a, b) > 0; }

int Less(Time *a, Time *b) { return Cmp(a, b) < 0; }

// ����������С������,�ֱ������ϵĺ��������.
Man Min, Max;

int main(int argc, char *argv[]) {
  int n;
  int i;
  int valid = 0;

  Max.bir.year = -1;
  Min.bir.year = 9999;

  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    Man tmp;
    scanf("%s %d/%d/%d", tmp.name, &tmp.bir.year, &tmp.bir.month, &tmp.bir.day);
    if (Valid(&tmp.bir)) {
      ++valid;
      if (More(&tmp.bir, &Max.bir)) {
        Max = tmp;
      }
      if (Less(&tmp.bir, &Min.bir)) {
        Min = tmp;
      }
    }
  }
  if (valid) {
    // ע��,Min�����ϵ�,Max���������.
    printf("%d %s %s\n", valid, Min.name, Max.name);
  } else {
    printf("0\n");
  }
  return 0;
}
