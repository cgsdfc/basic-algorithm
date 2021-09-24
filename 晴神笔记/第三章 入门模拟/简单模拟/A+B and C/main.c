#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef long long LL;

int Sgn(long long x) { return x == 0 ? 0 : (x > 0 ? 1 : -1); }

char *Bool(int x) { return x ? "true" : "false"; }

//参考答案的解法,直接a+b,判断是否溢出.
int More(LL a, LL b, LL c) {
  LL res = a + b;
  if (a > 0 && b > 0 && res < 0) {
    // 正溢出. 必定大于c.
    return 1;
  }
  if (a < 0 && b < 0 && c > 0) {
    // 负溢出,必定小于c.
    return 0;
  }
  return res > c;
}

int main(int argc, char *argv[]) {
  int i;
  int n;

  scanf("%d", &n);
  for (i = 1; i <= n; ++i) {
    long long a, b, c;
    int res;
    scanf("%lld%lld%lld", &a, &b, &c);
    printf("Case #%d: ", i);

    if (Sgn(a) != Sgn(b)) {
      //			异号相加不可能溢出.
      res = a + b > c;
    } else {
      if (Sgn(a) == Sgn(c)) {
        //				同号相减不可能溢出.
        res = b > c - a;
      } else {
        //				ab同号,ac异号,比较符号即可.
        res = Sgn(a) > Sgn(c);
      }
    }

    printf("%s\n", Bool(res));
  }
  return 0;
}
