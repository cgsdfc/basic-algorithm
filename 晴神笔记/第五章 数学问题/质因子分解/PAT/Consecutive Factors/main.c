#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef long long ll;

/*
在N的因子序列中，找到一个子序列，满足：
1. 子序列的元素是连续的。
2. 子序列的元素乘积小于等于N，即子序列是N的一个分解的一部分。
3. 子序列的长度是满足1，2条件中最长的。
4. 子序列的起始元素大小是满足1，2，3中最小的。

算法：
找到两个因子，它们是连续的。
在满足2的情况下，向后扩展子序列。
当子序列无法再扩展时，记录长度len。
继续向后找更多子序列，更新最大长度和子序列起始元素位置。
*/

/*
注意，枚举i，即序列的开头元素时，要连续的枚举，才能过第2个点。
如果每次i总是跳到j，则第二个点不过。
也就是说，一个序列从i开始，到j结束，长度是len，则从i+1开始的序列，长度可能超过
len。这是有可能的，比如60，第一个序列：2 3，因为2*3*4=24 所以不能到5了。
但是3 4 5却刚好60，这两个序列是有重叠的，并且后一个比前一个长。
为什么会这样呢？因为当一个序列不可以再变长时，并不一定是N不够大了，而是N剩下的部分
不能被序列的最后一个元素的下一个整除，这时候可以舍弃序列的前缀，向前移动，可能获取更长的序列。
*/
void Find(ll N) {
  ll i;
  ll sqr;
  ll max = -1;
  ll pos;

  sqr = sqrt(N);

  //	printf("N %lld sqr %lld\n", N, sqr);

  for (i = 2; i <= sqr; ++i) {
    ll j;
    ll p;
    ll len;

    if (N % i != 0) {
      //			++i;
      continue;
    }

    p = i;
    j = i + 1;
    while (j <= sqr && N % (p * j) == 0) {
      //			printf("j %lld p %lld\n", j,p);
      p *= j;
      ++j;
    }

    //		printf("i %lld j %lld\n",i,j);

    len = j - i;
    if (len > max) {
      max = len;
      pos = i;
    }
    //		i=j;
  }
  if (max == -1) {
    // N是素数。
    max = 1;
    pos = N;
  }
  printf("%d\n", max);
  for (i = pos; i < pos + max; ++i) {
    if (i == pos) {
      printf("%d", i);
    } else {
      printf("*%d", i);
    }
  }
  printf("\n");
}

/*
实际上不需要枚举N的全部因子，
只需要枚举小于等于sqrtN的因子即可。
因为一个因子如果大于sqrtN，那么它的长度只能是1.
而任意一个小于等于sqrtN的因子的序列，它最短都是1.
鉴于长度相同而要求开始元素最小，所以大于sqrtN的因子可以不考虑。
*/
int main(int argc, char *argv[]) {
  ll N;

  scanf("%lld", &N);
  Find(N);
  return 0;
}
