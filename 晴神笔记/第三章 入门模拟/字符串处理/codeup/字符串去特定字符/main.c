#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
/*
��Ŀ����
�����ַ���s���ַ�c��Ҫ��ȥ��s�����е�c�ַ�������������

����
���������ж��飬ÿ�������ַ���s���ַ�c��

���
����ÿ������,���ȥ��c�ַ���Ľ����

�������� Copy
goaod
a
������� Copy
good
*/

#define MAXN 1000

int main(int argc, char *argv[]) {
  char str[MAXN];
  char c;

  while (gets(str) && scanf("%c", &c) != EOF) {
    int i;
    int k;
    int len = strlen(str);

    getchar();
    k = 0;
    /*
    ˳���ɾ�������ض�Ԫ�أ�����Ҫ˳�������
    */
    for (i = 0; i < len; ++i) {
      if (str[i] != c) {
        str[k++] = str[i];
      }
    }
    str[k] = 0;
    puts(str);
  }

  return 0;
}
