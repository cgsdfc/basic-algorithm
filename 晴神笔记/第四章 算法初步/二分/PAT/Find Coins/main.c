#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
本题解法如下：
1. 哈希（散列）
2. 二分查找。
*/

int N, M;

#define MAXN 100005

int a[MAXN];
/*
二分的做法：
先对序列按从小到大排序，因为题目要求V1小于等于V2，并且输出V1最小那个结果。
所以从小到大枚举V1，再向后查找V2，第一个查找成功的就是答案。

为什么只需要从V1的后面查找？
如果V2在V1的前面，（即V2大于V1）
按照我们从小到大的顺序，在前面处理V2的时候，就会找到V1了，因此不可能再处理V1.
而且，如果从V1开始查找，则即使找到了V1的下标，也不是答案，故应该从V1的下一个元素开始找。

当i到达最后一个元素时，已经不存在下一个元素了，因此i不必到达最后一个。
*/

int CMP(const void *_a, const void *_b) { return *(int *)_a - *(int *)_b; }

int main(int argc, char *argv[]) {
  int i;

  scanf("%d%d", &N, &M);
  for (i = 0; i < N; ++i) {
    scanf("%d", &a[i]);
  }
  qsort(a, N, sizeof(int), CMP);
  for (i = 0; i < N - 1; ++i) {
    int x = M - a[i];
    int *res = bsearch(&x, a + i + 1, N - i - 1, sizeof(int), CMP);
    if (res) {
      printf("%d %d\n", a[i], x);
      return 0;
    }
  }
  puts("No Solution");

  return 0;
}
