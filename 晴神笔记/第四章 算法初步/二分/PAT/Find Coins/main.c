#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
����ⷨ���£�
1. ��ϣ��ɢ�У�
2. ���ֲ��ҡ�
*/

int N, M;

#define MAXN 100005

int a[MAXN];
/*
���ֵ�������
�ȶ����а���С����������Ϊ��ĿҪ��V1С�ڵ���V2���������V1��С�Ǹ������
���Դ�С����ö��V1����������V2����һ�����ҳɹ��ľ��Ǵ𰸡�

Ϊʲôֻ��Ҫ��V1�ĺ�����ң�
���V2��V1��ǰ�棬����V2����V1��
�������Ǵ�С�����˳����ǰ�洦��V2��ʱ�򣬾ͻ��ҵ�V1�ˣ���˲������ٴ���V1.
���ң������V1��ʼ���ң���ʹ�ҵ���V1���±꣬Ҳ���Ǵ𰸣���Ӧ�ô�V1����һ��Ԫ�ؿ�ʼ�ҡ�

��i�������һ��Ԫ��ʱ���Ѿ���������һ��Ԫ���ˣ����i���ص������һ����
*/

int CMP(const void *_a, const void *_b) { return *(int *)_a - *(int *)_b; }

int main(int argc, char *argv[]) {
  int i;

  scanf("%d%d", &N, &M);
  for (i = 0; i < N; ++i) {
    scanf("%d", &a[i]);
  }
  qsort(a, N, sizeof(int), CMP);
  for (i = 0; i < N - 1; ++i) {
    int x = M - a[i];
    int *res = bsearch(&x, a + i + 1, N - i - 1, sizeof(int), CMP);
    if (res) {
      printf("%d %d\n", a[i], x);
      return 0;
    }
  }
  puts("No Solution");

  return 0;
}
