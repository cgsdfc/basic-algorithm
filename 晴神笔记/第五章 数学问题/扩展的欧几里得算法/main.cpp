#include <assert.h>
#include <stdio.h>

// 扩展的gcd算法，以及求乘法逆元。

// ax+by=gcd
int extgcd(int a, int b, int &x, int &y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  int g = extgcd(b, a % b, x, y);
  // x'=y; y'=x-a/b*y
  int temp = x;
  x = y;
  y = temp - a / b * y;
  return g;
}

// 1/a mod m
int inverse(int a, int m) {
  int x, y;
  int g = extgcd(a, m, x, y);
  assert(g == 1);
  // 最后必须把x映射到 （0，m）范围内，因为x可以出现负数。
  return (x % m + m) % m;
}

int main(int argc, char const *argv[]) {
  int a = 7;
  int m = 40;
  int a_inv = inverse(a, m);
  printf("a %d m %d 1/a %d\n", a, m, a_inv);
  return 0;
}
