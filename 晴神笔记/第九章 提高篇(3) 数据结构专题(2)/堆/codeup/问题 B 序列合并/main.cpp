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
    �󶥶ѡ�
    */
    void DownAdjust(int low, int hi) {
        int i = low;
        int j = 2 * i;
        while (j <= hi) {
            if (j + 1 <= hi && heap[j + 1] > heap[j]) {
                // �Һ��Ӹ���
                j++;
            }
            if (heap[j] > heap[i]) {
                // ���Ӹ���
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
ά��һ���󶥶ѣ�ʹ��Ԫ��ֻ��N����
��ʼʱ����ѵ�Ԫ��ΪA0��B�ĸ���Ԫ�ء�
Ȼ�����ѭ��ɨ��A��Bʣ�µ�Ԫ�أ�����˵��ɨ��
A1��B�ĸ���Ԫ�أ�A2��B�ĸ���Ԫ�أ��ȵȡ�
ö��һ��Ԫ��ʱ����������ڵ��ڶѶ�����ζ�Ŷ���Ԫ�ض�����
��ǰ�棬���Ե�ǰԪ�ز�������ǰNС����Ϊ����N��Ԫ�أ���
����ɾ���Ѷ����ѵ�ǰԪ�ؼ���ѣ���Ϊ���ȶѶ�С����Ѷ������������Ԫ�ص�
����ʽ��������N��Ԫ���ǵ�ǰ��֪��N����СԪ�ء�
ͬʱע�⣬������ǰԪ�ش��ڵ��ڶѶ�ʱ��˵����ǰ�еĺ���Ԫ��ֻ�ܸ��󣬴�ʱҪ����ѭ����
��������㷨���Ӷ��� N^2logN
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
        // ��֤heap��ʼ����N��Ԫ�ء�
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
        // heap�е�Ԫ�ؾ������󣬵�������
        heap.Sort();
        heap.Print();
    }

    return 0;
}
