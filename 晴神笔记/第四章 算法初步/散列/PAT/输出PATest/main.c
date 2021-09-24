#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

const char Chars[] = "PATest";

#define MAXN 10005

int Hash(char c) {
  int i;
  for (i = 0; i < 6; ++i) {
    if (Chars[i] == c)
      return i;
  }
  return -1;
}

char UnHash(int h) {
  assert(0 <= h && h < 6);
  return Chars[h];
}

int hashtable[10];
char str[MAXN];

int main(int argc, char *argv[]) {
  int len, i;
  int tot = 0; // �ܹ�Ҫ������ַ�����

  gets(str);
  for (i = 0, len = strlen(str); i < len; ++i) {
    int h = Hash(str[i]);
    if (h != -1) {
      // ͳ��ĳ���ַ��ж��١�
      hashtable[h]++;
      ++tot;
    }
  }
  // ע�����ѭ����д����tot�������ѭ�����ڲ�ѭ����0--6�����ַ����顣
  while (tot) {
    for (i = 0; i < 6; ++i) {
      if (hashtable[i] > 0) {
        putchar(UnHash(i));
        --hashtable[i];
        --tot;
      }
    }
  }
  putchar('\n');
  return 0;
}
