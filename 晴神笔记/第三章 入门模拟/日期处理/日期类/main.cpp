#include <stdio.h>
#include <stdlib.h>

/*
����
�����һ�б�ʾ���������ĸ���m��������m��ÿ����3���ÿո�������������ֱ��ʾ�����ա��������ݲ��������ꡣ

���
���m�С���xxxx-xx-xx�ĸ�ʽ�������ʾ�������ڵĺ�һ������ڡ�
*/

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
const int Days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Time {
  int yy, mm, dd;

  // ��һ�졣
  void Add() {
    ++dd;
    if (dd == Days[mm] + 1) {
      dd = 1;
      ++mm;
    }
    if (mm == 13) {
      mm = 1;
      ++yy;
    }
  }

  void Print() { printf("%04d-%02d-%02d\n", yy, mm, dd); }
};

int main(int argc, char *argv[]) {
  int m;

  while (scanf("%d", &m) != EOF) {
    while (m--) {
      Time t;
      scanf("%d%d%d", &t.yy, &t.mm, &t.dd);
      t.Add();
      t.Print();
    }
  }
  return 0;
}
