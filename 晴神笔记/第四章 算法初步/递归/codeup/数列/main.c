#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
��N=Nʱ��Ҫ�õ�2N-1��쳲�����������0��ʼ����
ע����������Ķ�Ӧ��ϵ�����������N������쳲��������Ĺ�ϵ��
����Ŀո�͵�i�еĹ�ϵ����i�к͸���Ҫ��������Ķ��ٵĹ�ϵ��
���о���N������10����ʾN���10.
*/

#define MAXN 10
#define MAXM (MAXN * 2)

int a[MAXM];

void Fill(int n) {
  int i;
  a[0] = 0;
  a[1] = 1;
  for (i = 2; i <= n; ++i) {
    a[i] = a[i - 1] + a[i - 2];
  }
}

void Print(int n) {
  int i;
  for (i = 0; i < n; ++i) {
    // ��ӡ�ո�
    int space = 2 * (n - i - 1);
    int j;
    while (space--) {
      putchar(' ');
    }
    for (j = 0; j < 2 * i + 1; ++j) {
      printf("%d%s", a[j], j == 2 * i ? "\n" : " ");
    }
  }
}

int main(int argc, char *argv[]) {
  int M;
  int i;

  Fill(2 * MAXN - 2);

  scanf("%d", &M);
  while (M--) {
    int N;
    scanf("%d", &N);
    Print(N);
  }

  return 0;
}
