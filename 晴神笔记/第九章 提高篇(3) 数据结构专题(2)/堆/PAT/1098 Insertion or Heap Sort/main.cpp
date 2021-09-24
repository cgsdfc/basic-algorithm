#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int N;
#define MAXN 105
int origin[MAXN]; // 原始未排序序列。
int temp[MAXN];   // origin的拷贝。
int now[MAXN];    // 经过几轮排序后的序列。

/*
直接模拟两种排序。
*/
void DownAdjust(int A[], int low, int high) {
  int i = low;
  int j = i * 2;
  while (j <= high) {
    if (j + 1 <= high && A[j + 1] > A[j]) {
      // 右孩子更大。
      j = j + 1;
    }
    if (A[j] > A[i]) {
      // 孩子比父节点大。
      swap(A[i], A[j]);
      i = j;
      j = 2 * i;
    } else {
      break; // 调整结束。
    }
  }
}

void CreateHeap(int A[], int N) {
  for (int i = N / 2; i >= 1; --i) {
    // 逆序，非叶子节点建堆。
    DownAdjust(A, i, N);
  }
}

void Print(int A[], int N) {
  for (int i = 1; i <= N; ++i) {
    printf("%d%s", A[i], i == N ? "\n" : " ");
  }
}

// 注意堆排序的下标从1到N。
// 为了一致性，全部下标都是1到N。

void HeapSort(int A[], int N) {
  CreateHeap(A, N);
  bool flag = false;

  // 堆的大小从N减小到1.
  for (int i = N; i > 1; i--) {
    swap(A[1], A[i]);
    DownAdjust(A, 1, i - 1); // 对剩下的元素进行Down。
    if (flag) {
      puts("Heap Sort");
      Print(A, N);
      return;
    }
    if (!memcmp(A + 1, now + 1, sizeof(int) * N)) {
      flag = true; // 找到目标序列。
    }
  }
}

/*
由于堆排序使用1--N下标，注意memcpy，memcmp和输出的相应调整。
*/

void InsertSort(int A[], int N) {
  bool flag = false;

  // 把2--N 元素插入有序序列，初始为1号。
  for (int i = 2; i <= N; ++i) {
    int temp = A[i]; // 取出待插入元素，腾出空间。
    int j = i;
    // 在一个有序序列里插入元素temp，关键是从后往前，
    // 找到一个第一个位置j，使得j-1的元素小于等于 temp
    // 或者j就是第一个位置。
    while (j > 1 && A[j - 1] > temp) {
      A[j] = A[j - 1];
      j--;
    }
    A[j] = temp; // 找到合适位置。
    if (flag) {
      puts("Insertion Sort");
      Print(A, N);
      return;
    }
    if (!memcmp(A + 1, now + 1, sizeof(int) * N)) {
      flag = true;
    }
  }
}

int main(int argc, char **argv) {
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) {
    scanf("%d", &origin[i]); // 输入原始序列。
  }
  for (int i = 1; i <= N; ++i) {
    scanf("%d", &now[i]); // 输入部分排序后的序列。
  }
  memcpy(temp + 1, origin + 1, sizeof(int) * N);
  HeapSort(temp, N);
  memcpy(temp + 1, origin + 1, sizeof(int) * N);
  InsertSort(temp, N);

  return 0;
}
