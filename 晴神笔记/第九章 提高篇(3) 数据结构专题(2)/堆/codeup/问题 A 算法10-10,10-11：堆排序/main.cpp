#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN (100000 + 5)

// 简单的堆排序模拟。
// 用大顶堆。

int N;
int data[MAXN];

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

void DownAdjust(int low, int hi) {
  int i = low;
  int j = 2 * i;
  while (j <= hi) {
    if (j + 1 <= hi && data[j + 1] > data[j]) {
      ++j;
    }
    if (data[j] > data[i]) {
      swap(data[i], data[j]);
      i = j;
      j = 2 * i;
    } else {
      break;
    }
  }
}

void CreateHeap() {
  for (int i = N / 2; i >= 1; --i) {
    DownAdjust(i, N);
  }
}

void HeapSort() {
  CreateHeap();
  for (int i = N; i > 1; --i) {
    swap(data[1], data[i]);
    DownAdjust(1, i - 1);
  }
}

int main(int argc, char **argv) {
  while (scanf("%d", &N) != EOF) {
    for (int i = 1; i <= N; ++i) {
      scanf("%d", &data[i]);
    }
    HeapSort();
    for (int i = 1; i <= N; ++i) {
      printf("%d ", data[i]);
    }
    printf("\n");
  }
  return 0;
}
