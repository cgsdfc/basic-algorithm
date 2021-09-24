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
  当A数字比B数字短时，要在A的高位补零，而不是直接复制A到C。
  因为题目的意思是要以0对齐两个数字，而不是只按照B的长度来。
  若只按照B的长度来，不按A，B长度的最大值来，则有2组数据通不过。
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
      // 注意存的是字符数组，取出来元素当作一位整数运算，结果要转为数字字符
      // 存入结果数组。输出时，务必按照字符输出。
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
