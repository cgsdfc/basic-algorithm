#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100

int all[MAXN][10];
int N;
// �����ʱ���ɵ�һ���⡣
int P[10];
int hashtable[10];

/*
ע�⣬����˻ʺ�����ʱ�����Ҫôͳһ��0��ʼ���±꣬
Ҫôͳһ��1��ʼ���±꣬���߰����鿪��һЩ���ɡ�
*/

// ���ֵ����ҳ��˻ʺ�����н⡣
void FindAll(int index) {
  if (index == 9) {
    // �ݹ���ڣ��Ѿ�����һ�����С�
    int i, j;
    int ok = 1;
    for (i = 1; i <= 8; ++i) {
      for (j = i + 1; j <= 8; ++j) {
        // i�У� Pi�У�j�У�Pj�С�
        if (abs(i - j) == abs(P[i] - P[j])) {
          // ����ͬһ���Խ���
          ok = 0;
          break;
        }
      }
    }
    if (ok) {
      for (i = 0; i < 8; ++i) {
        all[N][i] = P[i];
      }
      ++N;
    }
    return;
  }
  // ��index���ʺ�Ӧ�÷�����һ�С�
  int i;
  for (i = 1; i <= 8; ++i) {
    if (!hashtable[i]) {
      P[index] = i;
      hashtable[i] = 1;
      FindAll(index + 1);
      hashtable[i] = 0;
    }
  }
}

int main(int argc, char *argv[]) {
  int n;
  int i;

  freopen("./in.txt", "r", stdin);
  FindAll(1);

  //	printf("%d\n", N);
  //	for (i=0;i<N;++i) {
  //		int j;
  //		for (j=1;j<=8;++j) {
  //			printf("%d ", all[i][j]);
  //		}
  //		puts("");
  //	}

  while (scanf("%d", &n) != EOF) {
    while (n--) {
      int b;
      int i;
      scanf("%d", &b);
      for (i = 1; i <= 8; ++i) {
        printf("%d", all[b - 1][i]);
      }
      printf("\n");
    }
  }
  return 0;
}
