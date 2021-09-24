#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 110
// 注意是0-9的英文。
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
  以下步骤，可以用
  sprintf(num, "%d", sum);
  代替，然后对num进行遍历输出即可。
  */
  i = 0;
  do {
    // num is char[], large enough to hold int 0-9.
    num[i++] = sum % 10;
    sum /= 10;
  } while (sum);
  // 要逆序遍历num，而这种写法恰好可以逆序遍历。
  while (i--) {
    printf("%s", Eng[num[i]]);
    printf("%s", i == 0 ? "\n" : " ");
  }
  return 0;
}
