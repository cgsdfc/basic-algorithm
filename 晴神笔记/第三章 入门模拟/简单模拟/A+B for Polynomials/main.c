#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
/*
���ʹ���ܼ��洢,��ϲ�ͬ�����ȥ��0,��Ҫʵ��˳����㷨,
�Ƚ��鷳.��Ȼ���Խ�ʡ�ռ�.

��ʹ��ϡ��洢,��ϲ�ͬ����ȽϷ���,����0�����ֱ�����������.
������Ҫ��һ���Ƚϴ��������ָ����ֱ��ӳ��.
*/

// ָ��Ϊi��ϵ��������a[i]��.
#define MAXN 1005
double a[MAXN];

int main(int argc, char *argv[]) {
  int k1, k2, k3; // ��������ʽ�ķ�����.
  int i;

  // �����һ������ʽ.
  scanf("%d", &k1);
  for (i = 0; i < k1; ++i) {
    int e;
    double c;
    scanf("%d%lf", &e, &c);
    a[e] += c;
  }

  // ����ڶ�������ʽ,�����ӷ�.
  scanf("%d", &k2);
  for (i = 0; i < k2; ++i) {
    int e;
    double c;
    scanf("%d%lf", &e, &c);
    a[e] += c;
  }
  k3 = 0;
  for (i = 0; i < MAXN; ++i) {
    if (a[i])
      ++k3;
  }
  //ע��,���k3==0,�������k3�����пո�.
  printf("%d", k3);
  for (i = MAXN - 1; i >= 0; --i) {
    if (a[i] != 0.0) {
      printf(" %d %.1f", i, a[i]);
    }
  }
  return 0;
}
