#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 26����д��ĸ��10�����֣�1���ո�
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
������ʵ��������ַ����Ǻõģ�������Ӧ�������ַ�������������ʵ�������ַ��Ķ��ǻ��ġ�
���ַ�ֻ���һ�Ρ�
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
      // ���ַ�����������Ļ��ַ���
      continue;
    }
    hashtable[h] = 2;
    putchar(islower(ch) ? toupper(ch) : ch);
  }
  putchar('\n');

  return 0;
}
