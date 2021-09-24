#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
4.5.1 二分查找的几个算法和模板。
1. 二分查找，查找是否存在满足某个条件的元素。
2. upper-bound，上界，第一个大于x的元素的位置。
3. lower-bound，下界， 第一个大于等于x的元素的位置。
4. 广义二分查找模板，要查找第一个满足某条件的元素的位置，
则用upper-bound模板，把条件改改即可。若要查找最后一个满足某条件的元素，
则转化为第一个不满足条件的位置-1.
*/

// [left, right], -1 if not found. 0-based index.
int binarySearch(int A[], int left, int right, int x) {
  int mid;
  while (left <= right) {
    mid = (left + right) / 2; // 如果怕溢出，用 left+(right-left)/2
    if (A[mid] == x) {
      return mid; // 逮个正着。
    }
    if (A[mid] > x) {
      // 左边去
      right = mid - 1;
    } else {
      // 右边去
      left = mid + 1;
    }
  }
  return -1;
}

/*
注意，binarySearch相比upper/lower-bound，是特殊情况，
后者才是更一般的二分查找，因为方程近似根也可以套用后者。
*/

// 第一个大于x的元素的下标， [0, n]
int upper_bound(int A[], int left, int right, int x) {
  int mid;
  // 注意没有等于。
  while (left < right) {
    // 就本问题而言，左边的一半不满足，右边的一半满足条件（这里的一半并不是
    // 真的一半）。
    mid = (left + right) / 2;
    if (A[mid] > x) {
      // 满足了条件，说明我们在右边满足条件的一半，但是我们要找的是满足条件的
      // 第一个，即两边的分界线，所以要向左去。
      right = mid;
    } else {
      // 中点不满足条件，说明我们还在左边不满足的一半，所以去右边。
      left = mid + 1;
    }
    // 直到区间只有一个元素，说明我们已经到了边界线，并且是满足条件的一侧。
    // left-1 就是最后一个小于等于x的元素。
  }
  // 这种模板求出来的，就是第一个满足条件的下标，也就是两边分界线靠满足条件的一侧。
  return left;
}

// 第一个大于等于x的元素的下标，[0,n]
int lower_bound(int A[], int left, int right, int x) {
  int mid;
  while (left < right) {
    if (A[mid] >= x) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}

/*
注意，lower/upper-bound返回的下标范围是0-n，即包含了越界的下标，所以必须先判断
是否越界，才能用来访问数组。
*/

/*
二分查找通用模板。查找满足某条件的第一个元素。
注意，这个条件必须是在序列中先不满足，然后满足，才能用该模板，否则就要根据实际情况调整。
left，right的初值必须覆盖所有可能的取值。
这个模板不仅适用于数组查找，也可用于解其他问题，比如木棍分割，凸多边形外接圆半径，根的近似值。
这些问题如果是离散的取值，也可以用顺序查找，但二分查找可以提高效率；如果是连续的取值，则必须二分查找。
*/
int Template(int left, int right) {
  int mid;
  while (left < right) {
    mid = (left + right) / 2;
    if (/* 条件成立 */ 1) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}
