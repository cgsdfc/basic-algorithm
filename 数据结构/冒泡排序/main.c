#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
ð������Ļ���˼��

�ȶ���һ�˵Ĳ�����
һ�˲�������ԭ�����һ�������С�ɨ�������е�ÿһ��Ԫ�أ������Ԫ�ر����ұߵ�Ԫ�ظ���
����߽�����������Ч����ʹ�ô������С�������ұߡ�һ�˽����󣬸������е����Ԫ�����������е����

����n-1�ˣ�ÿһ�˵������ж���0��ʼ������λ�����n-1�ݼ���1 ��
ִ��n-1�˺󣬾͵õ�����������顣
*/

static void BubbleSort(int a[], int size) {
  int i, j;

  // i ö��ÿһ�˵Ľ���λ�á�
  for (i = size - 1; i >= 1; --i) {
    // j ö�������еĵ�ǰԪ�ء�
    // ��ΪҪ��j�ұߵ����� ����j��ȥ�������е����һ��Ԫ�ء�
    for (j = 0; j <= i - 1; ++j) {
      if (a[j] > a[j + 1]) {
        // ��ߵ�����
        int tmp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = tmp;
      }
    }

    //		WriteArray(stdout, a, size);
  }
}

#define MAXN 100

int main(int argc, char *argv[]) {
  int a[MAXN];
  int n;

  n = 10;
  RandArray(a, n);
  //	n=ReadArray(stdin, a, MAXN);
  WriteArray(stdout, a, n);

  BubbleSort(a, n);
  WriteArray(stdout, a, n);

  return 0;
}
