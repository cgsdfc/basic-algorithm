#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 25

int count;   // �ܷ�������
int N;       // Ԫ�ظ�����
int K;       // �Ӽ���С��
int A[MAXN]; // ȫ����

int IsPrime(int N) {
  int i;
  int sqr;

  if (N <= 1)
    return 0;
  sqr = sqrt(N);
  for (i = 2; i <= sqr; ++i) {
    if (N % i == 0)
      return 0;
  }
  return 1;
}

void DFS(int index, int nowK, int sum) {
  // �ɹ��ĳ��ڡ�
  if (nowK == K && IsPrime(sum)) {
    ++count;
    //		printf("sum %d\n", sum);
    return;
  }
  // ʧ�ܵĳ��ڡ�
  if (index == N || nowK == K) {
    return;
  }
  DFS(index + 1, nowK, sum);
  DFS(index + 1, nowK + 1, sum + A[index]);
}

int main(int argc, char *argv[]) {
  while (scanf("%d%d", &N, &K) != EOF) {
    int i;
    for (i = 0; i < N; ++i) {
      scanf("%d", &A[i]);
    }
    count = 0;
    DFS(0, 0, 0);
    printf("%d\n", count);
  }
  return 0;
}
