#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
/*
��Ŀ����

�������ıƽ����������� y(n+1) = y(n)*2/3 +
x/(3*y(n)*y(n)),����y0=x.�������x����n�ε�������������ֵ��


����

�����ж������ݡ�
ÿ��һ�У�����x n��


���

����n�κ����������double����,����С���������λ��


�������� Copy
4654684 1
65461 23
������� Copy
3103122.666667
40.302088
*/

int main(int argc, char *argv[]) {
  int x, n;
  while (scanf("%d%d", &x, &n) != EOF) {
    double y = x;
    while (n--) {
      y = y * 2 / 3 + x / (3 * y * y);
    }
    printf("%.6f\n", y);
  }
  return 0;
}
