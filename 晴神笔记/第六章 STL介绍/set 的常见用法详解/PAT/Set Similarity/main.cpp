#include <iostream>
#include <set>
#include <stdio.h>
using namespace std;

typedef set<int> Set;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
#define MAXN 55
Set sets[MAXN];

double results[MAXN * MAXN];

double Rate(Set &a, Set &b) {
  int common = 0;
  int total = b.size();
  for (Set::iterator it = a.begin(); it != a.end(); ++it) {
    if (b.find(*it) != b.end()) {
      // b有，a也有。
      ++common;
    } else {
      // a有，b没有。
      total++;
    }
  }
  return (double)common / total * 100;
}

int Hash(int i, int j, int N) { return i * N + j; }

void RateAll(int N) {
  for (int i = 1; i <= N; ++i) {
    for (int j = i; j <= N; ++j) {
      double rate = i == j ? 100 : Rate(sets[i], sets[j]);
      int h = Hash(i, j, N);
      results[h] = rate;
    }
  }
}

/*
总集合数N比较小，而M，K比较大，因此适合预计算所有集合对的Common和Total，
然后查询。
优化前：KMlogM

优化后：N^2 MlogM + K
*/

int main(int argc, char **argv) {
  int N;
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) {
    int M;
    scanf("%d", &M);
    while (M--) {
      int x;
      scanf("%d", &x);
      sets[i].insert(x);
    }
  }
  RateAll(N);

  int K;
  scanf("%d", &K);
  while (K--) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (a > b) {
      swap(a, b);
    }
    double rate = results[Hash(a, b, N)];
    printf("%.1f%%\n", rate);
  }
  return 0;
}
