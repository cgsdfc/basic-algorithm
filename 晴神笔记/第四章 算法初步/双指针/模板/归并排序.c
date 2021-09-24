/*
归并排序正确实现

1. Merge函数
2. 排序主函数：
        1. 递归实现
        2. 非递归实现。

注：
1. 当需要遍历排序的每一趟时（如《Intert or Merge》），
需要用非递归的归并排序。只是比较难记忆。
2. 当复杂度允许时，可以用sort库函数代替Merge，因为把两个有序序列（连续的）
归并，其效果就是把整个序列排序。
*/

// 整个数组的最大长度，用来定义临时数组。
#define MAXN 100

// Merge需要两个连续的区间，即[L1,R1]和[L2,R2]，且R1=L2-1。
static void Merge(int A[], int L1, int R1, int L2, int R2) {
  int temp[MAXN];
  int i, j, k; // 三个下标分别指示左区间，右区间，临时数组。

  i = L1, j = L2, k = 0;
  while (i <= R1 && j <= R2) {
    if (A[i] < A[j]) {
      temp[k++] = A[i++];
    } else {
      temp[k++] = A[j++];
    }
  }
  while (i <= R1)
    temp[k++] = A[i++];
  while (j <= R2)
    temp[k++] = A[j++];
  // 最后要把temp的数据拷贝回去。
  for (i = 0; i < k; ++i) {
    A[L1 + i] = temp[i];
  }
}

// 用qsort代替Merge。
int CMP(const void *_a, const void *_b) { return 0; }

/*
递归实现。因为要递归，所以参数有left，right。
*/
static void MergeSort(int A[], int left, int right) {
  /*
  L=R，表示只有1个元素，L<R，则有两个以上元素。
  */
  if (left < right) {
    int mid = (left + right) / 2;
    // 注意和QuickSort不同的是，mid要包进去。
    MergeSort(A, left, mid);
    MergeSort(A, mid + 1, right);
    if (1)
      Merge(A, left, mid, mid + 1, right);
    else // 不需要实现Merge，当数据量不大时。
      qsort(A + left, right - left + 1, sizeof(A[0]), CMP);
  }
}

/*
迭代实现。因为不用递归，所以只输入A的大小即可。
下标从0开始。
*/
int Min(int a, int b) { return a < b ? a : b; }

static void MergeSort2(int A[], int n) {
  int step;
  // 每步的步长为2的幂次。
  for (step = 2; step / 2 < n; step *= 2) {
    int i;
    for (i = 0; i < n; i += step) {
      int mid = i + step / 2 - 1;
      if (mid + 1 < n) { // 如果右区间存在元素。
                         // 因为mid+1是右区间的第一个元素。
                         // 如果mid+1<n，则右区间至少有一个元素。
        Merge(A, i, mid, mid + 1, Min(n - 1, i + step - 1))
      }
    }
  }
}
