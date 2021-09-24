#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
双指针法枚举所有连续的合数序列，找最长的合数序列。
如果有多个最长序列，输出第一个即可。

打素数表可以把复杂度降到O(N)，否则（逐个判断素数）复杂度是 O(N * sqrtN)
*/

const int MAXN = 1e6 + 5;
bool p[MAXN];

void FindPrime() {
  // 筛法。
  for (int i = 2; i < MAXN; ++i) {
    if (!p[i]) {
      // i是素数，标记它的倍数。
      for (int j = i * 2; j < MAXN; j += i) {
        p[j] = true;
      }
    }
  }
}

int N; // 1--N。

int main(int argc, char **argv) {
  scanf("%d", &N);
  FindPrime();

  int maxLen = 0;
  int start;
  int i = 4; // 1，2，3 都不是合数。
  while (i <= N) {
    while (i <= N && !p[i]) {
      ++i; // p=true是合数。
    }
    int j = i;
    while (j <= N && p[j]) {
      ++j;
    }
    int len = j - i;
    //		for (int k=i;k<j;++k) {
    //			printf("%d%s", k,k==j-1?"\n":" ");
    //		}

    if (len > maxLen) {
      maxLen = len;
      start = i;
    }
    i = j;
  }
  for (int i = start, n = start + maxLen; i < n; ++i) {
    printf("%d%s", i, i == n - 1 ? "\n" : " ");
  }
  return 0;
}
