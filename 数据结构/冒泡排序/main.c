#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
冒泡排序的基本思想

先定义一趟的操作：
一趟操作的是原数组的一个子序列。扫描子序列的每一个元素，如果该元素比它右边的元素更大，
则二者交换。这样的效果是使得大的数在小的数的右边。一趟结束后，该子序列的最大元素排在子序列的最后。

共有n-1趟，每一趟的子序列都从0开始，结束位置则从n-1递减到1 。
执行n-1趟后，就得到了有序的数组。
*/

static void BubbleSort(int a[], int size) {
  int i, j;

  // i 枚举每一趟的结束位置。
  for (i = size - 1; i >= 1; --i) {
    // j 枚举子序列的当前元素。
    // 因为要看j右边的数， 所以j不去到子序列的最后一个元素。
    for (j = 0; j <= i - 1; ++j) {
      if (a[j] > a[j + 1]) {
        // 左边的数大。
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
