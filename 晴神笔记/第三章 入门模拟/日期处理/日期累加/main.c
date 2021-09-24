#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
��Ŀ����
���һ�������ܼ���һ�����ڼ������������ʲô���ڡ�

����
�����һ�б�ʾ��������m��������m��ÿ���ĸ������ֱ��ʾ�����պ��ۼӵ�������

���
���m�У�ÿ�а�yyyy-mm-dd�ĸ��������

�������� Copy
1
2008 2 3 100
������� Copy
2008-05-13
*/

int MonDays(int yy, int mm) {
  int leap = (yy % 4 == 0 && yy % 100 != 0) || (yy % 400 == 0);
  switch (mm) {
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    return 31;
  case 4:
  case 6:
  case 9:
  case 11:
    return 30;
  case 2:
    return 28 + leap;
  default:
    return -1;
  }
}

int main(int argc, char *argv[]) {
  int m;

  while (scanf("%d", &m) != EOF) {
    while (m--) {
      int yy, mm, dd;
      int n;

      scanf("%d%d%d%d", &yy, &mm, &dd, &n);
      while (n--) {
        ++dd;
        if (dd == MonDays(yy, mm) + 1) {
          dd = 1;
          ++mm;
        }
        if (mm == 13) {
          mm = 1;
          ++yy;
        }
      }
      printf("%04d-%02d-%02d\n", yy, mm, dd);
    }
  }
  return 0;
}
