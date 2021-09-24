#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// K �����Ӹ�����
#define MAXK (400 + 5)

// ���������б�
typedef struct List {
  int data[MAXK];
  int len;
} List;

List ans;
List temp;

int K;           // ���Ӹ�����
int N;           // ���ֽ��������
int P;           // ���ӵ�ָ����
int MaxSum = -1; // ��ǰ��������Ӻ͡�

// ������������ a**b.
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
a��b���ǵ������У���ĿҪ��ݼ����У������ֵ���Ҫ���
������Ƚ�a��b��
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
�Ӵ�Сö�����ӣ�ʹ�����ɵ����������ǰ����ֵ���ݼ��ģ�
������֤��ͬ���Ӻ͵������������ֵ���

���Ȿ������ҪѡȡK����������ʹ�����ǵ��ݺ�Ϊ��ֵ�����ǵ���K������˳����㲻ͬ��
��Ҳ����ͬ�ģ����ö�ٵ�ʱ��Ҫ�ظ�ö�١�����ö��K��������i+1��Ԫ�غ͵�i��Ԫ����ȣ�
Ҫô��ȣ�Ҫô��1������ö�ٳ��������е��ֵ����Ǵ�С��������ģ����Ҳ�������Ԫ����ͬ����
˳��ͬ�������Ҳ���ǲ��ظ���

X����ǰ���ǵ����ӡ�
nowK����ǰ�����Ӹ�����
nowSum����ǰ�����Ӻ͡�
nowN����ǰ�������ݺ͡�
*/
void DFS(int X, int nowK, int nowN, int nowSum) {
  int i;
  int max; // ��ǰԪ�ز��ܳ��������

  // �߽硣
  if (nowK == K) {
    //		assert(temp.len == K);

    // �Ϸ��⡣
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

  // �ڵ�ǰԪ�صĻ����ϵ�����
  //	max=pow(N-nowN-K+nowK+1, 1.0/P);
  for (i = X; Pow(i, P) + nowN + (K - nowK - 1) <= N; ++i) {
    // ��������д��Ҳ�ᳬʱ��
    //	for (i=X; i<=max; ++i) {
    temp.data[temp.len++] = i;
    DFS(i, nowK + 1, nowN + Pow(i, P), nowSum + i);
    temp.len--;
  }
}

/*
�ֵ���Ӵ�Сö�١�
����ᳬʱ��
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
    // û��һ���Ϸ��⡣
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
