#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1000

int ans[MAXN];

/*
��Ŀ˵�����ӣ�����ָ�����ӣ�����1Ҳ��һ�����ӣ�
����ָ����������N���Ҳ�����N������
��N���������Ӻ������������Ӳ�ͬ��

ֻҪö��1--N���������ɡ�
�����Ż���sqrtN����Ϊ��P�����ӣ���N/PҲ�����ӡ�
������PС�ڵ���sqrtN����N/P���ڵ���sqrtN������ö��1--sqrtN���ɡ�

�ɼ����ֽ�����������Բ��õ�������
��Ȼ��һ���������������ĺͣ�Ҳ�������������Ĺ�ʽ������û��Ҫ��
*/

int Judge(int N) {
  int sum = 0;
  int sqr;
  int i;

  // 1����������
  if (N == 1)
    return 0;
  sqr = sqrt(N);

  //	printf("sqr %d\n", sqr);

  for (i = 1; i <= sqr; ++i) {
    if (N % i == 0) {
      int p = N / i;
      sum += i;
      if (p != N && p != i) {
        sum += p;
      }
    }
  }
  return sum == N;
}

int main(int argc, char *argv[]) {
  int N;

  while (scanf("%d", &N) != EOF) {
    int j;
    int num = 0; // ����������

    //		printf("%d\n", N);

    for (j = 2; j <= N; ++j) {
      if (Judge(j)) {
        ans[num++] = j;
      }
    }
    //		printf("num %d\n", num);

    for (j = 0; j < num; ++j) {
      printf("%d%s", ans[j], j == num - 1 ? "\n" : " ");
    }
  }
  return 0;
}
