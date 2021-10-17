#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
using namespace std;

#define MAXN (100000 + 5)
int N;

struct Heap {
    int heap[MAXN];
    int N;
    /*
    大顶堆。
    */
    void DownAdjust(int low, int hi) {
        int i = low;
        int j = 2 * i;
        while (j <= hi) {
            if (j + 1 <= hi && heap[j + 1] > heap[j]) {
                // 右孩子更大。
                j++;
            }
            if (heap[j] > heap[i]) {
                // 孩子更大。
                swap(heap[j], heap[i]);
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
    int Top() {
        return heap[1];
    }
    void DeleteTop() {
        heap[1] = heap[N--];
        DownAdjust(1, N);
    }
    void UpAdjust(int low, int hi) {
        int i = hi;
        int j = i / 2;
        while (j >= low) {
            if (heap[i] > heap[j]) {
                swap(heap[i], heap[j]);
                i = j;
                j = i / 2;
            } else {
                break;
            }
        }
    }
    void Insert(int x) {
        heap[++N] = x;
        UpAdjust(1, N);
    }
    void Init() {
        N = 0;
    }
    void Sort() {
        for (int i = N; i > 1; i--) {
            swap(heap[1], heap[i]);
            DownAdjust(1, i - 1);
        }
    }
    void Print() {
        for (int i = 1; i <= N; ++i) {
            printf("%d%s", heap[i], i == N ? "\n" : " ");
        }
    }
};

Heap heap;
int A[MAXN], B[MAXN];

/*
维护一个大顶堆，使其元素只有N个。
初始时，令堆的元素为A0加B的各个元素。
然后二重循环扫描A，B剩下的元素，比如说，扫描
A1加B的各个元素，A2加B的各个元素，等等。
枚举一个元素时，如果它大于等于堆顶，意味着堆内元素都排在
它前面，所以当前元素不可能是前N小（因为堆有N个元素）。
否则，删除堆顶，把当前元素加入堆，因为它比堆顶小，则堆顶不再满足堆内元素的
不变式，即堆内N个元素是当前已知的N个最小元素。
同时注意，遇到当前元素大于等于堆顶时，说明当前行的后面元素只能更大，此时要跳出循环。
但是这个算法复杂度是 N^2logN
*/

int main(int argc, char** argv) {
    while (scanf("%d", &N) != EOF) {
        heap.Init();
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &A[i]);
        }
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &B[i]);
            heap.Insert(A[1] + B[i]);
        }
        // 保证heap开始就有N个元素。
        for (int i = 2; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                int top = heap.Top();
                int now = A[i] + B[j];
                if (now < top) {
                    heap.DeleteTop();
                    heap.Insert(now);
                } else {
                    break;
                }
            }
        }
        // heap中的元素就是所求，但是无序。
        heap.Sort();
        heap.Print();
    }

    return 0;
}
