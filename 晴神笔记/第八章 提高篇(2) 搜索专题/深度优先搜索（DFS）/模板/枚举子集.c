#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
DFS ö��N��Ԫ�ص�ȫ�������ظ�Ԫ���Ӽ���
��Ϊö�ٵ���ȫ���Ӽ�������Ԫ���ǲ��������ظ��ģ���������������
*/

// ȫ����С ��
static int N;
// �Ӽ��Ľ�����
static int K;

#define MAXN 100

// N �����ظ�Ԫ�ء�
static int A[MAXN];

/*
��ǰö�ٳ������Ӽ���
*/
struct {
  int data[MAXN];
  int len;
} ans;

/*
ö��ȫ���Ӽ���
����ö�ٵó����Ӽ������������ԣ�
1. ���ظ���ÿ����ͬ�Ӽ�ֻ����һ�Ρ�
2. �Ӽ�����Ԫ�ص�����
3. �Ӽ����ֵ���������֡�
*/

static void DFS(int index) {
  if (index == N) {
    int i;
    // �ѿ���������Ԫ�أ��õ�һ���Ӽ���
    printf("len %d data", ans.len);
    for (i = 0; i < ans.len; ++i) {
      printf(" %d", ans.data[i]);
    }
    printf("\n");
    return;
  }
  // ѡ index��
  ans.data[ans.len++] = A[index];
  DFS(index + 1);
  ans.len--;

  // ��ѡ index��
  DFS(index + 1);
}

/*
ö��K���Ӽ���
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
    // ����������Ԫ�أ������Ӽ���С����K��
    return;
  }

  // ѡ index��
  ans.data[ans.len++] = A[index];
  DFS2(index + 1, nowK + 1);
  ans.len--;

  // ��ѡ index��
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
���ô��������߾��ȣ�ʵ�ַǵݹ�ö���Ӽ���
��NΪ�������壬��ȡNλ�����ƴ������������� N=3��
ö�� 000--111 ֮��2^N��������ͨ���ӷ���������ÿ��������
��������һ���Ӽ���Ԫ�ص�ȷ�����£�

��iλ��1�����i��Ԫ�ؼ����Ӽ������� �����롣

����ö�ٳ������Ӽ�����Щ�ص㣺
1. �����ڲ����±�����ġ�
2. �Ӽ�������˳�����ֵ�������ġ�
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
�ҵ����д�СΪK���Ӽ���
ֻ��Ҫ��ö��ȫ���Ӽ��Ļ����ϣ�������С�պ�ΪK���Ӽ����ɡ�
*/
static void FindAllSubsets2(int N, int K) {
  char bit[MAXN] = {}; // ��ʼΪ�ռ���
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
