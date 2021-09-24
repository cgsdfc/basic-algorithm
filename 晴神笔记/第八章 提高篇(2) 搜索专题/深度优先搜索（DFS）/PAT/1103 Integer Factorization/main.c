#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// K 是因子个数。
#define MAXK (400 + 5)

// 保存因子列表。
typedef struct List {
  int data[MAXK];
  int len;
} List;

List ans;
List temp;

int K;           // 因子个数。
int N;           // 待分解的整数。
int P;           // 因子的指数。
int MaxSum = -1; // 当前的最大因子和。

// 整数的整数幂 a**b.
int Pow(int a, int b) {
  if (b == 0)
    return 1;
  if (b & 1) {
    // ODD.
    return a * Pow(a, b - 1);
  } else {
    int ans = Pow(a, b / 2);
    return ans * ans;
  }
}

/*
a，b都是递增序列，题目要求递减序列，并且字典序要最大，
故逆序比较a，b。
*/
int CMP(int a[], int b[], int len) {
  int i;
  for (i = len - 1; i >= 0; --i) {
    if (a[i] != b[i]) {
      return a[i] - b[i];
    }
  }
  return 0;
}

/*
从大到小枚举因子，使得生成的因子序列是按照字典序递减的，
这样保证相同因子和的序列有最大的字典序。

问题本质上是要选取K个正整数，使得它们的幂和为定值，考虑到这K个数的顺序就算不同，
和也是相同的，因此枚举的时候不要重复枚举。于是枚举K个数，第i+1个元素和第i个元素相比，
要么相等，要么大1。这样枚举出来的序列的字典序是从小到大递增的，并且不可能有元素相同但是
顺序不同的情况，也就是不重复。

X：当前考虑的因子。
nowK：当前的因子个数。
nowSum：当前的因子和。
nowN：当前的因子幂和。
*/
void DFS(int X, int nowK, int nowN, int nowSum) {
  int i;
  int max; // 当前元素不能超过这个。

  // 边界。
  if (nowK == K) {
    //		assert(temp.len == K);

    // 合法解。
    if (nowN == N) {
#ifndef ONLINE_JUDGE
      int i;
      printf("sum %d\n", nowSum);
      for (i = 0; i < temp.len; ++i) {
        printf("%d ", temp.data[i]);
      }
      printf("\n");
#endif
      if (nowSum > MaxSum ||
          (nowSum == MaxSum && CMP(temp.data, ans.data, ans.len) > 0)) {
        ans = temp;
        MaxSum = nowSum;
      }
    }
    return;
  }

  // 在当前元素的基础上递增。
  //	max=pow(N-nowN-K+nowK+1, 1.0/P);
  for (i = X; Pow(i, P) + nowN + (K - nowK - 1) <= N; ++i) {
    // 下面这种写法也会超时。
    //	for (i=X; i<=max; ++i) {
    temp.data[temp.len++] = i;
    DFS(i, nowK + 1, nowN + Pow(i, P), nowSum + i);
    temp.len--;
  }
}

/*
字典序从大到小枚举。
这个会超时。
*/
void DFS2(int X, int nowK, int nowN, int nowSum) {
  int i;
  if (nowK == K) {

    if (nowN == N) {
#ifndef ONLINE_JUDGE
      int i;
      printf("sum %d nowN %d\n", nowSum, nowN);
      for (i = 0; i < temp.len; ++i) {
        printf("%d ", temp.data[i]);
      }
      printf("\n");
#endif
      if (nowSum > MaxSum) {
        MaxSum = nowSum;
        ans = temp;
      }
    }
    return;
  }
  for (i = X; i >= 1; --i) {
    temp.data[temp.len++] = i;
    DFS2(i, nowK + 1, nowN + Pow(i, P), nowSum + i);
    temp.len--;
  }
}

int Main1(void) {
  int X;
//	int i;
//	for (i=1;i<=10;++i) {
//		printf("%d\n", Pow(2, i));
//	}
//	return 0;
#ifndef ONLINE_JUDGE
  freopen("./in.txt", "r", stdin);
#endif

  scanf("%d%d%d", &N, &K, &P);

  DFS(1, 0, 0, 0);
  //	X=pow(N-K+1, 1.0/P);
  //	printf("X %d\n", X);
  //	DFS2(X, 0, 0, 0);

  if (MaxSum == -1) {
    // 没有一个合法解。
    printf("Impossible\n");
  } else {
    int i;
    // 169 = 6^2 + 6^2 + 6^2 + 6^2 + 5^2
    printf("%d = ", N);
    //		for (i=0;i<ans.len;++i) {
    //			printf("%d^%d%s", ans.data[i], P, i==ans.len-1?"\n":" +
    //");
    //		}
    for (i = ans.len - 1; i >= 0; i--) {
      printf("%d^%d%s", ans.data[i], P, i == 0 ? "\n" : " + ");
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  Main2();
  return 0;
}
