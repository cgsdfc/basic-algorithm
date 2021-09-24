#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
typedef struct Big {
  int d[MAXN];
  int len;
  int intlen;
} Big;

int Max(int a, int b) { return a > b ? a : b; }

// 小数部分长度
int FracLen(char str[], int len) {
  int i;
  for (i = 0; i < len; ++i) {
    if (str[i] == '.')
      break;
  }
  return len - i;
}

Big From(char str[], int len, int fill) {
  int i;
  Big c = {};

  while (fill--) {
    c.d[c.len++] = 0;
  }

  for (i = len - 1; i >= 0; i--) {
    if (str[i] == '.') {
      // 小数点的下标正好是整数的长度。
      c.intlen = i;
    } else {
      c.d[c.len++] = str[i] - '0';
    }
  }
  return c;
}

Big a, b;

void Init(char s1[], int len1, char s2[], int len2) {
  int flen1, flen2;
  int max;

  flen1 = FracLen(s1, len1);
  flen2 = FracLen(s2, len2);
  max = Max(flen1, flen2);
  a = From(s1, len1, max - flen1);
  b = From(s2, len2, max - flen2);
}

/*
去掉小数后面的0
*/
Big Fix(Big a) {
  int i;
  int flag;
  int len;

  len = 0;
  flag = 1;
  for (i = 0; i < a.len; ++i) {
    if (flag && a.d[i] == 0 && i < a.len - a.intlen)
      continue;
    flag = 0;
    a.d[len++] = a.d[i];
  }
  a.len = len;
  return a;
}

void Print(Big a) {
  int j;
  /*
  可能有前导零或者尾零？
  01.12 1.200
  */
  a = Fix(a);

  for (j = a.len - 1; j >= 0; --j) {
    printf("%d", a.d[j]);
    if (j == a.len - a.intlen) {
      // 整数结束了
      printf(".");
    }
  }
  printf("\n");
}

// 两个对齐的高精度相加。
Big Add(void) {
  int i;
  int carry = 0;
  Big c = {};

  for (i = 0; i < a.len || i < b.len; ++i) {
    int temp = carry + a.d[i] + b.d[i];
    c.d[c.len++] = temp % 10;
    carry = temp / 10;
  }
  if (carry) {
    c.d[c.len++] = carry;
  }
  /*
  c的小数长度和a，b的小数长度一样。
  */
  c.intlen = c.len - (a.len - a.intlen);
  return c;
}

/*
2
3.756
90.564

4543.5435
43.25
*/

/*
题目的几点重要前提：
1. 输入数据
        整数部分每一位非负。
        小数部分最后一位非零。
2. 输出数据
        小数部分不为0.
所以，输入不需要对0做特殊处理，输出只要把小数部分的多余0去掉即可。
*/
int main(int argc, char *argv[]) {
  char s1[MAXN], s2[MAXN];
  int N;

  while (scanf("%d", &N) != EOF) {
    while (N--) {
      scanf("%s%s", s1, s2);
      Init(s1, strlen(s1), s2, strlen(s2));
      //			Print(a);
      //			Print(b);

      Print(Add());
    }
  }
  return 0;
}
