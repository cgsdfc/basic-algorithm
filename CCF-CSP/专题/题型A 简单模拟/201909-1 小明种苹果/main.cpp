#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N; // ƻ����������
int M; // ����������

// ���ߴ�������Ҫ���顣

int T, K, P; // Tʣ��ƻ��������Kƻ����������ƻ������PΪ����ٵ�ƻ������

int main(int argc, char **argv) {
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= N; ++i) {
    int all;     // ��ǰ��ƻ����������ǰ����
    int tot = 0; // ����ƻ����������
    scanf("%d", &all);
    for (int j = 0; j < M; ++j) {
      int op;
      scanf("%d", &op); // �Ե�ǰƻ�������в�����
      if (op < 0) {
        // ���в�����
        all += op;
        tot -= op;
      }
    }
    T += all;
    if (tot > P) {
      P = tot;
      K = i;
    }
  }
  printf("%d %d %d\n", T, K, P);

  return 0;
}
