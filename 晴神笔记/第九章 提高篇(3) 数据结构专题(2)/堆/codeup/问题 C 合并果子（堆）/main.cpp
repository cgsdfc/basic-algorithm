#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
̰�Ĳ��ԣ�
��ǰ�Ĺ��Ӷѷ��ڶ��У�
ÿ�δӶ���ȡ����С��2�ѹ��ӣ��ϲ���Ȼ��Żض��С�
������֤ÿ�κϲ���
1. �ϲ��Ĵ�������С�ġ�
2. �¹��Ӷ�����С�ģ��������Ժ�ĺϲ���

������ֻʣ��һ�����Ӷ�ʱ����õ��ܵ�������ͬʱ����һ�ߺϲ�һ�߼����ܴ��ۡ�
*/

#define MAXN (30000 + 5)

struct Heap {
  // С���ѣ�ʵ����С���۵��ȳ�����
  int N;
  int data[MAXN];

  void Init() { N = 0; }
  void Down(int low, int hi) {
    // ���µ�����
    int i = low;
    int j = i * 2;
    while (j <= hi) {
      if (j + 1 <= hi && data[j + 1] < data[j]) {
        j++;
      }
      if (data[j] < data[i]) {
        // ���Ӹ�С��
        swap(data[j], data[i]);
        i = j;
        j = 2 * i;
      } else {
        break;
      }
    }
  }
  void Up(int low, int hi) {
    // ���ϵ�����
    int i = hi;
    int j = i / 2;
    while (j >= low) {
      if (data[j] > data[i]) {
        // ���׸���
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
int N; // �ܹ�������

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
