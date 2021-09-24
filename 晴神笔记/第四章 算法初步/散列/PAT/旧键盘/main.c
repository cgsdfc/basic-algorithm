#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 26个大写字母，10个数字，1个空格
#define MAXN (26 + 10 + 1 + 5)

int Hash(char c) {
  if (c == '_')
    return 0;
  if ('0' <= c && c <= '9')
    return c - '0' + 1;
  if ('A' <= c && c <= 'Z')
    return c - 'A' + 11;
  if ('a' <= c && c <= 'z')
    return c - 'a' + 11;
}

/*
出现在实际输入的字符都是好的，出现在应该输入字符，但不出现在实际输入字符的都是坏的。
坏字符只输出一次。
*/
int hashtable[MAXN];

#define MAXS 100

char should[MAXS];
char actual[MAXS];

int main(int argc, char *argv[]) {
  int i;
  int len;

  gets(should);
  gets(actual);
  for (i = 0, len = strlen(actual); i < len; ++i) {
    int h = Hash(actual[i]);
    hashtable[h] = 1;
  }
  for (i = 0, len = strlen(should); i < len; ++i) {
    char ch = should[i];
    int h = Hash(ch);
    if (hashtable[h] == 1 || hashtable[h] == 2) {
      // 好字符或者已输出的坏字符。
      continue;
    }
    hashtable[h] = 2;
    putchar(islower(ch) ? toupper(ch) : ch);
  }
  putchar('\n');

  return 0;
}
