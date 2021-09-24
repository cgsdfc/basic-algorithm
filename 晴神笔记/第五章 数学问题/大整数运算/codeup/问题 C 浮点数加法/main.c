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

// С�����ֳ���
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
      // С������±������������ĳ��ȡ�
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
ȥ��С�������0
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
  ������ǰ�������β�㣿
  01.12 1.200
  */
  a = Fix(a);

  for (j = a.len - 1; j >= 0; --j) {
    printf("%d", a.d[j]);
    if (j == a.len - a.intlen) {
      // ����������
      printf(".");
    }
  }
  printf("\n");
}

// ��������ĸ߾�����ӡ�
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
  c��С�����Ⱥ�a��b��С������һ����
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
��Ŀ�ļ�����Ҫǰ�᣺
1. ��������
        ��������ÿһλ�Ǹ���
        С���������һλ���㡣
2. �������
        С�����ֲ�Ϊ0.
���ԣ����벻��Ҫ��0�����⴦�����ֻҪ��С�����ֵĶ���0ȥ�����ɡ�
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
