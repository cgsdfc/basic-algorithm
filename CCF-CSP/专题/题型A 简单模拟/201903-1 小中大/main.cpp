#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N;
int Min, Max, Mid;

int main(int argc, char **argv) {
  /*
  ��Сֵ�����ֵ����������
  ż������λ���������м�����ƽ��ֵ�������Ǹ�������
  */
  scanf("%d", &N);
  bool odd = N & 1;

  /*
  ע�⣬���ݿ���Ϊ������߽��򣡣���
  */
  for (int i = 0; i < N; ++i) {
    int x;
    scanf("%d", &x);
    // ��һ��������Сֵ��
    if (i == 0) {
      Min = x;
    }
    if (i == N - 1) {
      Max = x;
    }
    if (odd && i == N / 2) {
      Mid = x;
    }
    if (!odd && (i == N / 2 || i == N / 2 - 1)) {
      Mid += x;
    }
  }
  // �ؼ���
  if (Max < Min) {
    swap(Max, Min);
  }

  printf("%d ", Max);
  if (odd) {
    printf("%d", Mid);
  } else {
    if (Mid % 2 == 0) {
      // ��λ����������
      printf("%d", Mid / 2);
    } else {
      printf("%.1f", (double)Mid / 2);
    }
  }
  printf(" %d\n", Min);
  return 0;
}
