#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

//计算 a/b，将结果四舍五入。
int RoundDiv(int a, int b) {
  if (a % b * 2 >= b) {
    // 余数大于半个b 。
    return a / b + 1;
  }
  return a / b;
}

int main(int argc, char *argv[]) {
  int c1, c2;
  int dur;

  scanf("%d%d", &c1, &c2);
  dur = c2 - c1;

  // 手动对dur四舍五入。
  if (dur % 100 >= 50) {
    // 在把dur从tick为单位转化为s为单位时，
    //		可以避免浮点运算，就是在进行除法之前判断余数是否大于等于除数的一半。
    //这也是四舍五入的一半原理。 这里实际上实现了对 dur/100
    //进行四舍五入的操作，即 round(dur/100.0)。
    dur = dur / 100 + 1;
  } else {
    dur = dur / 100;
  }

  printf("%02d:%02d:%02d\n", dur / 3600, (dur % 3600) / 60, dur % 60);

  return 0;
}
