#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
DFS 枚举N个元素的全集的无重复元素子集。
因为枚举的是全部子集，所以元素是不能无限重复的，否则有无数个。
*/

// 全集大小 。
static int N;
// 子集的阶数。
static int K;

#define MAXN 100

// N 个不重复元素。
static int A[MAXN];

/*
当前枚举出来的子集。
*/
struct {
  int data[MAXN];
  int len;
} ans;

/*
枚举全部子集。
这种枚举得出的子集具有两种特性：
1. 不重复，每个不同子集只出现一次。
2. 子集序列元素递增。
3. 子集以字典序递增出现。
*/

static void DFS(int index) {
  if (index == N) {
    int i;
    // 已考虑了所有元素，得到一个子集。
    printf("len %d data", ans.len);
    for (i = 0; i < ans.len; ++i) {
      printf(" %d", ans.data[i]);
    }
    printf("\n");
    return;
  }
  // 选 index。
  ans.data[ans.len++] = A[index];
  DFS(index + 1);
  ans.len--;

  // 不选 index。
  DFS(index + 1);
}

/*
枚举K阶子集。
*/
static void DFS2(int index, int nowK) {
  if (nowK == K) {
    int i;
    for (i = 0; i < ans.len; ++i) {
      printf("%d ", ans.data[i]);
    }
    printf("\n");
    return;
  }
  if (index == N) {
    // 考虑了所有元素，但是子集大小不足K。
    return;
  }

  // 选 index。
  ans.data[ans.len++] = A[index];
  DFS2(index + 1, nowK + 1);
  ans.len--;

  // 不选 index。
  DFS2(index + 1, nowK);
}

void PrintAllSubset(void) {
  int i;
  scanf("%d", &N);
  for (i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }
  DFS(0);
}

void PrintAllSubset2(void) {
  int i;
  scanf("%d%d", &N, &K);
  for (i = 0; i < N; ++i) {
    A[i] = i;
  }
  DFS2(0, 0);
}

/*
利用大整数（高精度）实现非递归枚举子集。
设N为上述意义，则取N位二进制大整数，不妨设 N=3，
枚举 000--111 之间2^N个整数（通过加法），对于每个整数，
它代表了一个子集，元素的确定如下：

第i位是1，则第i个元素加入子集，否则 不加入。

这样枚举出来的子集有这些特点：
1. 序列内部是下标递增的。
2. 子集产生的顺序是字典序递增的。
*/

static int NextSubset(char bit[], int N) {
  int i;
  int carry = 1;

  ans.len = 0;
  for (i = 0; i < N; ++i) {
    int a = bit[i];
    bit[i] = a ^ carry;
    carry &= a;
    if (bit[i]) {
      ans.data[ans.len++] = i;
    }
  }
  return !carry;
}

static void FindAllSubsets(int N) {
  char bit[MAXN] = {};
  memset(&ans, 0, sizeof(ans));
  do {
    int i;
    printf("len %d data ", ans.len);
    for (i = 0; i < ans.len; ++i) {
      printf("%d ", ans.data[i]);
    }
    printf("\n");
  } while (NextSubset(bit, N));
}

/*
找到所有大小为K的子集。
只需要在枚举全部子集的基础上，保留大小刚好为K的子集即可。
*/
static void FindAllSubsets2(int N, int K) {
  char bit[MAXN] = {}; // 初始为空集。
  int count = 0;

  memset(&ans, 0, sizeof(ans));
  do {
    int i;
    if (ans.len != K) {
      continue;
    }
    for (i = 0; i < ans.len; ++i) {
      printf("%d ", ans.data[i]);
    }
    printf("\n");
    ++count;
  } while (NextSubset(bit, N));
  printf("%d\n", count);
}

void PrintAllSubset3(void) {
  int i;
  scanf("%d", &N);
  for (i = 0; i < N; ++i) {
    A[i] = i;
  }
  FindAllSubsets(N);
}

void PrintAllSubset4(void) {
  int i;
  scanf("%d%d", &N, &K);
  for (i = 0; i < N; ++i) {
    A[i] = i;
  }
  FindAllSubsets2(N, K);
}
