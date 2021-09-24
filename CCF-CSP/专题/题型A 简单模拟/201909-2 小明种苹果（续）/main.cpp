#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N; // ƻ����������

#define MAXN 1005

bool drop[MAXN];
int T; // ʣ�µ�������
int D; // ���������ƻ����������
int E; // �������������������

int main(int argc, char **argv) {
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) {
    int m;
    scanf("%d", &m);
    int all;           // ��ǰƻ��������
    scanf("%d", &all); // ��һ������һ����ͳ�Ƹ�����
    m--;
    while (m--) {
      int op;
      scanf("%d", &op);
      if (op > 0) {
        // ͳ��ƻ��������
        if (all > op) {
          // ���������䡣
          drop[i] = true;
        }
        all = op;
      } else {
        all += op;
      }
    }
    T += all;
    if (drop[i]) {
      //			printf("%d\n", i);
      ++D;
    }
  }
  for (int i = 1; i <= N; ++i) {
    // ���ÿһ��������ߣ��ұߣ��Լ��Ƿ����䡣
    int left = i == 1 ? N : i - 1;
    int right = i == N ? 1 : i + 1;
    if (drop[left] && drop[right] && drop[i]) {
      //			printf("%d %d %d\n", left, i, right);
      ++E;
    }
  }
  printf("%d %d %d\n", T, D, E);

  return 0;
}
