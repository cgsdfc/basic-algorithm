#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char *argv[]) {
  int N;
  while (scanf("%d", &N) != EOF) {
    /*
    ע�⣬x��y�����޿�ֱ����100����Ȼ��N��Сʱ����Ч������
    ����10000����������ȫ���ܵ�ס�ġ�
    */
    int x, y, z;
    for (x = 0; x <= 100; ++x) {
      for (y = 0; y <= 100 - x; ++y) {
        z = 100 - x - y;
        assert(x >= 0 && y >= 0 && z >= 0);
        // ע�⣬�����ø��������ܹ���
        if (x * 5 + y * 3 + z / 3.0 <= N) {
          printf("x=%d,y=%d,z=%d\n", x, y, z);
        }
      }
    }
  }
  return 0;
}
