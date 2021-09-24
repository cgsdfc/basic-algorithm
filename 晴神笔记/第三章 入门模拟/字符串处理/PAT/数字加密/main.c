#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 105

char a[MAXN];
char b[MAXN];
char c[MAXN];

// 1234567 368782971

const char radix[] = "0123456789JQK";

int main(int argc, char *argv[]) {
  int an, bn, cn = 0;
  int i;
  int j;
  int k;

  scanf("%s%s", a, b);
  an = strlen(a);
  bn = strlen(b);

  k = 1;
  /*
  ��A���ֱ�B���ֶ�ʱ��Ҫ��A�ĸ�λ���㣬������ֱ�Ӹ���A��C��
  ��Ϊ��Ŀ����˼��Ҫ��0�����������֣�������ֻ����B�ĳ�������
  ��ֻ����B�ĳ�����������A��B���ȵ����ֵ��������2������ͨ������
  */
  for (i = an - 1, j = bn - 1; i >= 0 || j >= 0; i--, j--, k++) {
    //	for (i=an-1,j=bn-1;i>=0&&j>=0;i--,j--,k++) {
    int res;
    int av = i >= 0 ? a[i] - '0' : 0;
    int bv = j >= 0 ? b[j] - '0' : 0;

    if (k % 2) {
      // odd
      res = (av + bv) % 13;
      c[cn++] = radix[res];
    } else {
      res = bv - av;
      //			printf("res=%d\n", res);
      if (res < 0)
        res += 10;
      // ע�������ַ����飬ȡ����Ԫ�ص���һλ�������㣬���ҪתΪ�����ַ�
      // ���������顣���ʱ����ذ����ַ������
      c[cn++] = res + '0';
    }
  }

  //	for (;j>=0;j--) {
  //		c[cn++]=b[j];
  //	}

  for (i = cn - 1; i >= 0; i--) {
    printf("%c", c[i]);
  }
  putchar('\n');
  return 0;
}
