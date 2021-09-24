#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 85

/*
��һ���ַ�����U�ͣ���ά���󣩵���ʽ������Ծ����������������Լ����
�� ���� Ϊn������Ϊm����������ֱ�۳���������ˮƽ�۳������㣺
1. N=2*n+m-2��N���ַ����ĳ��ȣ������ַ�����
2. n<=m����n������

�ɴ˿��Ƶ���n��m��N�Ĺ�ϵʽ�����ݲ���ʽ��ȡ���ֵ��ԭ����
1. n=floor( N+2) / 3 )
2. m=N+2-n*2

�ó�n��m���ٰ�Ҫ���ӡ������ֱ������İ취�������ÿ�����ʲô����ÿһ�У�
�����ÿ�����ʲô�����ҿ��ǵ������к��е���������У�ԭ�ַ�����˳��Ҳ�Ǵ����ҵģ�
������һ��k��¼��ǰ�ַ�����λ�ã������ҵ�Ҫ������ַ���
*/

int main(int argc, char *argv[]) {
  int n, m, N;
  char str[MAXN];
  int i, j, k;

  scanf("%s", str);
  N = strlen(str);
  n = (N + 2) / 3;
  m = N + 2 - 2 * n;

  //	printf("n=%d, m=%d\n", n, m);

  k = 0;
  for (i = 0; i < n; ++i) {
    if (i != n - 1) {
      // ǰn-1�еĴ�ӡ��
      for (j = 0; j < m; ++j) {
        if (j == 0) {
          putchar(str[k]);
        } else if (j == m - 1) {
          putchar(str[N - 1 - k]);
        } else {
          putchar(' ');
        }
      }
      ++k; // ÿ��һ��
    } else {
      // ���һ�еĴ�ӡ
      for (j = 0; j < m; ++j) {
        putchar(str[k++]);
      }
    }
    putchar('\n');
  }
  return 0;
}
