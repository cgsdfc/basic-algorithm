#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 15

const char Dig[][5] = {"ling", "yi",  "er", "san", "si",
                       "wu",   "liu", "qi", "ba",  "jiu"};

// 不同组使用的后缀。
const char Suffix[][5] = {"", "Wan", "Yi"};

// 一组内使用的后缀 。
const char Pow[][5] = {"", "Shi", "Bai", "Qian"};

/*
从低位到高位分割成四位一组，每组求的一个十进制数字，若有相邻的数字0，
则合并成一个0.
每组先按照最低四位的叫法得出一个数，然后按照每组的位置加上一个后缀，
比如第一组没有后缀，第二组的后缀是万，第三组的后缀是亿。
如果一个组是0，则分几种情况：
如果从高到低，0后面没有其他项了，则不输出，比如一亿，而不是一亿零。
如果后面还有其他项，则输出ling，作为分隔符。

注意，单零0必须特判，不然这个0不会输出的。
*/

/*
Sample Input 1:
-123456789
Sample Output 1:
Fu yi Yi er Qian san Bai si Shi wu Wan liu Qian qi Bai ba Shi jiu
Sample Input 2:
100800
Sample Output 2:
yi Shi Wan ling ba Bai
*/

// 因为空格的输出比较难判断，索性就把所有字符串先存起来，然后就可以从容输出空格了。
const char *Res[MAXN];
int N;

void Add(const char val[]) { Res[N++] = val; }

// 打印一个四字符的组。
void PrintTerm(char str[], int n) {
  int i;

  for (i = 0; i < n; ++i) {
    int val = str[i] - '0';
    int power = n - i - 1;

    if (val) {
      Add(Dig[val]);
      if (power) {
        // 个位没有姓名
        Add(Pow[power]);
      }
    } else {
      if (i != n - 1 && str[i + 1] != '0') {
        Add(Dig[0]);
      }
    }
  }
}

// 因为需要判断下一个组组成的4位数是否为0，所以需要计算某组的整数值。
// str保存的数字是从高到低的。
int Atoi(char str[], int n) {
  int p = 1;
  int sum = 0;
  // 反向遍历str。
  while (n--) {
    sum += p * (str[n] - '0');
    p *= p;
  }
  return sum;
}

// 判断是否为0
int NonZero(char str[], int n) {
  int i;
  for (i = 0; i < n; ++i) {
    if (str[i] != '0')
      return 1;
  }
  return 0;
}

void Print(char str[], int n) {
  int r;
  int q;
  int i;
  int ngrp;

  if (str[0] == '0' && n == 1) {
    Add(Dig[0]);
    return;
  }
  if (str[0] == '-') {
    --n;
    ++str;
    Add("Fu");
  }

  q = n / 4;
  r = n % 4;
  ngrp = q + (r ? 1 : 0);

  for (i = 0; i < ngrp; ++i) {
    int len = (i == 0 && r) ? r : 4;
    if (NonZero(str, len)) {
      int power = ngrp - i - 1;
      PrintTerm(str, len);
      if (power) {
        Add(Suffix[power]);
      }
    } else if (i != ngrp - 1) {
      /*
      出现了0，但是只有在后面元素非零时才输出。
      也就是说，两个非零数之间连续的零被压缩成一个。
      而没有非零数兜着的零，直接不输出。
      */
      if (NonZero(str + len, 4)) { // 非首个组的长度必定为4.
        Add(Dig[0]);
      }
    }
    str += len;
  }
}

int main(int argc, char *argv[]) {
  char str[10];
  int n;
  int i;

  scanf("%s", str);
  n = strlen(str);
  Print(str, n);
  for (i = 0; i < N; ++i) {
    printf("%s%s", Res[i], i == N - 1 ? "\n" : " ");
  }
  return 0;
}
