#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
科学计数法是科学家用来表示很大或很小的数字的一种方便的方法，其满足正则表达式
[+-][1-9].[0-9]+E[+-][0-9]+， 即数字的整数部分只有 1 位，小数部分至少有 1
位，该数字及其指数部分的正负号即使对正数也必定明确给出。

现以科学计数法的格式给出实数 A，请编写程序按普通数字表示法输出
A，并保证所有有效位都被保留。

输入格式：
每个输入包含 1 个测试用例，即一个以科学计数法表示的实数
A。该数字的存储长度不超过 9999 字节， 且其指数的绝对值不超过 9999。

输出格式：
对每个测试用例，在一行中按普通数字表示法输出
A，并保证所有有效位都被保留，包括末尾的 0。

输入样例 1：
+1.23400E-03
输出样例 1：
0.00123400

输入样例 2：
-1.2E+10
输出样例 2：
-12000000000

*/

#define MAXN 10000

typedef struct Num {
  char sign; // 整个数的正负号，只有负号要输出。
  char fra[MAXN];
  int len; // fra的长度。
  int exp;
} Num;

void Print(Num n) { printf("%c %s %d\n", n.sign, n.fra, n.exp); }

Num Parse(char str[], int len) {
  int i;
  Num num;
  int n = 0;
  char exp[10];

  num.sign = str[0];
  num.fra[n++] = str[1];

  // i=2 是 .
  for (i = 3; str[i] != 'E'; ++i) {
    num.fra[n++] = str[i];
  }
  num.fra[n] = 0;
  num.len = n;
  n = 0;
  for (i++; i < len; ++i) {
    exp[n++] = str[i];
  }
  exp[n] = 0;
  // atoi 可以处理正负号。
  num.exp = atoi(exp);
  return num;
}

void Print2(Num n) {
  if (n.sign == '-')
    printf("%c", n.sign);
  if (n.exp < 0) {
    // 真小数。输出格式为0.000xxxx，即先是0，然后是fra。
    int i;
    printf("0.");
    // 1.2e-3 0.0012
    for (i = 0; i < -n.exp - 1; ++i) {
      putchar('0');
    }
    printf("%s", n.fra);
  } else {
    /*
    整数部分非零的假小数。
    先输出整数部分，然后是小数点，然后是剩余的尾数。
    有两种极端情况，
    1. 尾数位数很多，则必定有小数点和剩余的尾数。
    2. 指数很大，则不会有小数点，而且可能有0 。
    可以先输出尾数的第一位，然后一边继续输出尾数，一边计数用了多少指数。
    当尾数输完或者指数用完时，整数部分结束。接下来根据尾数是否输完和指数是否用完，
    补充小数点和剩下的尾数，或者补充指数的0 。
    */
    int i;
    int j;
    putchar(n.fra[0]);
    /*
    尾数成为整数部分输出，一边输出尾数，一边不能超过exp个字符。
    */
    for (i = 1, j = 0; i < n.len && j < n.exp; ++i, ++j)
      putchar(n.fra[i]);
    if (i < n.len) {
      // 尾数还没完。
      putchar('.');
      for (; i < n.len; ++i) {
        putchar(n.fra[i]);
      }
    } else {
      // 指数较大，需要补零。
      for (; j < n.exp; ++j) {
        putchar('0');
      }
    }
  }
  putchar('\n');
}

int main(int argc, char *argv[]) {
  char str[MAXN];
  Num num;

  scanf("%s", str);
  num = Parse(str, strlen(str));
  Print2(num);

  return 0;
}
