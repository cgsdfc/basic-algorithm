#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
/*
题目描述
输入字符串s和字符c，要求去掉s中所有的c字符，并输出结果。

输入
测试数据有多组，每组输入字符串s和字符c。

输出
对于每组输入,输出去除c字符后的结果。

样例输入 Copy
goaod
a
样例输出 Copy
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
    顺序表删除所有特定元素，不需要顺序表有序。
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
