#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
������N����������1--N����������N+1.
*/
#define MAXN (100000 + 1)
int prime[MAXN];
int p[MAXN];
int pNum;

/*
�����ɷ�Χ�ڵ�����������
Ȼ���ж����������Ƿ����2.
*/

void FindPrime(int N) {
  int i;
  int j;
  for (i = 2; i < MAXN && i <= N; ++i) {
    if (p[i] == 0) {
      prime[pNum++] = i;
      for (j = 2 * i; j < MAXN; j += i) {
        p[j] = 1;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int i;
  int N;
  int ans = 0;

  scanf("%d", &N);
  FindPrime(N);

  for (i = 0; i < pNum - 1; ++i) {
    if (prime[i + 1] - prime[i] == 2) {
      //			printf("%d %d\n", prime[i], prime[i+1]);
      ++ans;
    }
    //		printf("%d\n", prime[i]);
  }
  printf("%d\n", ans);

  return 0;
}
