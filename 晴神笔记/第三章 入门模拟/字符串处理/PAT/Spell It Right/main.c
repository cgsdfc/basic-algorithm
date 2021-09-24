#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 110
// ע����0-9��Ӣ�ġ�
const char Eng[][10] = {"zero", "one", "two",   "three", "four",
                        "five", "six", "seven", "eight", "nine"};

int main(int argc, char *argv[]) {
  char num[MAXN];
  int i, sum = 0;
  int len;

  scanf("%s", num);
  len = strlen(num);
  while (len--) {
    sum += num[len] - '0';
  }
  /*
  ���²��裬������
  sprintf(num, "%d", sum);
  ���棬Ȼ���num���б���������ɡ�
  */
  i = 0;
  do {
    // num is char[], large enough to hold int 0-9.
    num[i++] = sum % 10;
    sum /= 10;
  } while (sum);
  // Ҫ�������num��������д��ǡ�ÿ������������
  while (i--) {
    printf("%s", Eng[num[i]]);
    printf("%s", i == 0 ? "\n" : " ");
  }
  return 0;
}
