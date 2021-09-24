#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef long long LL;

int Sgn(long long x) { return x == 0 ? 0 : (x > 0 ? 1 : -1); }

char *Bool(int x) { return x ? "true" : "false"; }

//�ο��𰸵Ľⷨ,ֱ��a+b,�ж��Ƿ����.
int More(LL a, LL b, LL c) {
  LL res = a + b;
  if (a > 0 && b > 0 && res < 0) {
    // �����. �ض�����c.
    return 1;
  }
  if (a < 0 && b < 0 && c > 0) {
    // �����,�ض�С��c.
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
      //			�����Ӳ��������.
      res = a + b > c;
    } else {
      if (Sgn(a) == Sgn(c)) {
        //				ͬ��������������.
        res = b > c - a;
      } else {
        //				abͬ��,ac���,�ȽϷ��ż���.
        res = Sgn(a) > Sgn(c);
      }
    }

    printf("%s\n", Bool(res));
  }
  return 0;
}
