#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
贪心策略：
当前的果子堆放在堆中，
每次从堆中取出最小的2堆果子，合并，然后放回堆中。
这样保证每次合并，
1. 合并的代价是最小的。
2. 新果子堆是最小的，有利于以后的合并。

最后队列只剩下一个果子堆时，则得到总的数量，同时可以一边合并一边计算总代价。
*/

#define MAXN (30000 + 5)

struct Heap {
  // 小顶堆，实现最小代价的先出来。
  int N;
  int data[MAXN];

  void Init() { N = 0; }
  void Down(int low, int hi) {
    // 向下调整。
    int i = low;
    int j = i * 2;
    while (j <= hi) {
      if (j + 1 <= hi && data[j + 1] < data[j]) {
        j++;
      }
      if (data[j] < data[i]) {
        // 孩子更小。
        swap(data[j], data[i]);
        i = j;
        j = 2 * i;
      } else {
        break;
      }
    }
  }
  void Up(int low, int hi) {
    // 向上调整。
    int i = hi;
    int j = i / 2;
    while (j >= low) {
      if (data[j] > data[i]) {
        // 父亲更大。
        swap(data[j], data[i]);
        i = j;
        j = i / 2;
      } else {
        break;
      }
    }
  }
  void Insert(int x) {
    data[++N] = x;
    Up(1, N);
  }
  void DeleteTop() {
    data[1] = data[N--];
    Down(1, N);
  }
  int Top() { return data[1]; }
};

Heap heap;
int N; // 总果子数。

int main(int argc, char **argv) {
  while (scanf("%d", &N) != EOF) {
    heap.Init();
    for (int i = 0; i < N; ++i) {
      int x;
      scanf("%d", &x);
      heap.Insert(x);
    }
    int ans = 0;
    while (heap.N > 1) {
      int a = heap.Top();
      heap.DeleteTop();
      int b = heap.Top();
      heap.DeleteTop();
      int cost = a + b;
      ans += cost;
      heap.Insert(cost);
    }
    printf("%d\n", ans);
  }
  return 0;
}
